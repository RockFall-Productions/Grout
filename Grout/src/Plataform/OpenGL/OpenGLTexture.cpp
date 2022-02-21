#include "grtpch.h"
#include "OpenGLTexture.h"

#include "stb_image.h"

#include <fstream>

namespace Grout {
	void OpenGLFileHandler::ConvertUint(unsigned* array, unsigned int length) {
		unsigned int b1, b2, b3, b4;
		unsigned char* ptr;

		ptr = (unsigned char*)array;
		while (length--) {
			b1 = *ptr++;
			b2 = *ptr++;
			b3 = *ptr++;
			b4 = *ptr++;
			*array++ = (b1 << 24) | (b2 << 16) | (b3 << 8) | (b4);
		}
	}

	void OpenGLFileHandler::ConvertShort(unsigned short* array, unsigned int length) {
		unsigned short b1, b2;
		unsigned char* ptr;

		ptr = (unsigned char*)array;
		while (length--) {
			b1 = *ptr++;
			b2 = *ptr++;
			*array++ = (b1 << 8) | (b2);
		}
	}

	OpenGLFileHandler::ImageRec* OpenGLFileHandler::ImageOpen(const char* fileName)
	{
		//ImageOpenFallback(fileName);
		
		union {
			int testWord;
			char testByte[4];
		} endianTest;
		ImageRec* image;
		int swapFlag;
		int x;

		endianTest.testWord = 1;
		if (endianTest.testByte[0] == 1) {
			swapFlag = 1;
		}
		else {
			swapFlag = 0;
		}

		image = (ImageRec*)malloc(sizeof(ImageRec));
		if (image == NULL) {
			fprintf(stderr, "Out of memory!\n");
			exit(1);
		}

		image->file = fopen(fileName, "rb");
		if (image->file == NULL) {
			return NULL;
		}

		fread(image, 1, 12, image->file);

		if (swapFlag) {
			ConvertShort(&image->imagic, 6);
		}

		image->tmp = (unsigned char*)malloc(image->xsize * 256);
		if (image->tmp == NULL) {
			fprintf(stderr, "\nOut of memory!\n");
			exit(1);
		}

		if ((image->type & 0xFF00) == 0x0100) {
			x = image->ysize * image->zsize * (int)sizeof(unsigned);
			image->rowStart = (unsigned*)malloc(x);
			image->rowSize = (int*)malloc(x);
			if (image->rowStart == NULL || image->rowSize == NULL) {
				fprintf(stderr, "\nOut of memory!\n");
				exit(1);
			}
			image->rleEnd = 512 + (2 * x);
			fseek(image->file, 512, SEEK_SET);
			fread(image->rowStart, 1, x, image->file);
			fread(image->rowSize, 1, x, image->file);
			if (swapFlag) {
				ConvertUint(image->rowStart, x / (int)sizeof(unsigned));
				ConvertUint((unsigned*)image->rowSize, x / (int)sizeof(int));
			}
		}
		return image;
	}

	OpenGLFileHandler::ImageRec* OpenGLFileHandler::ImageOpenFallback(const char* fileName)
	{
		union {
			int testWord;
			char testByte[4];
		} endianTest;
		ImageRec* image;
		int swapFlag;
		int x;

		endianTest.testWord = 1;
		if (endianTest.testByte[0] == 1) {
			swapFlag = 1;
		}
		else {
			swapFlag = 0;
		}

		Ref<ImageRec> image_ref = CreateRef<ImageRec>();

		std::ifstream input(fileName, std::ios::binary);
		std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), {});

		char reading_buff;
		input.read(&reading_buff, 2);
		image_ref->imagic = (buffer[0] << 2 | buffer[1]);
		image_ref->type = buffer[1];
		image_ref->dim = buffer[2];
		image_ref->xsize = buffer[3];
		image_ref->ysize = buffer[4];
		image_ref->zsize = buffer[5];

		
		sizeof(unsigned short);


		if (swapFlag) {
			ConvertShort(&image->imagic, 6);
		}

		image->tmp = (unsigned char*)malloc(image->xsize * 256);
		if (image->tmp == NULL) {
			fprintf(stderr, "\nOut of memory!\n");
			exit(1);
		}

		if ((image->type & 0xFF00) == 0x0100) {
			x = image->ysize * image->zsize * (int)sizeof(unsigned);
			image->rowStart = (unsigned*)malloc(x);
			image->rowSize = (int*)malloc(x);
			if (image->rowStart == NULL || image->rowSize == NULL) {
				fprintf(stderr, "\nOut of memory!\n");
				exit(1);
			}
			image->rleEnd = 512 + (2 * x);
			fseek(image->file, 512, SEEK_SET);
			fread(image->rowStart, 1, x, image->file);
			fread(image->rowSize, 1, x, image->file);
			if (swapFlag) {
				ConvertUint(image->rowStart, x / (int)sizeof(unsigned));
				ConvertUint((unsigned*)image->rowSize, x / (int)sizeof(int));
			}
		}
		return image;
	}

	void OpenGLFileHandler::ImageClose(ImageRec* image) {
		fclose(image->file);
		free(image->tmp);
		free(image);
	}

	void OpenGLFileHandler::ImageGetRow(ImageRec* image, unsigned char* buf, int y, int z) {
		unsigned char* iPtr, * oPtr, pixel;
		int count;

		if ((image->type & 0xFF00) == 0x0100) {
			fseek(image->file, (long)image->rowStart[y + z * image->ysize], SEEK_SET);
			fread(image->tmp, 1, (unsigned int)image->rowSize[y + z * image->ysize],
				image->file);

			iPtr = image->tmp;
			oPtr = buf;
			for (;;) {
				pixel = *iPtr++;
				count = (int)(pixel & 0x7F);
				if (!count) {
					return;
				}
				if (pixel & 0x80) {
					while (count--) {
						*oPtr++ = *iPtr++;
					}
				}
				else {
					pixel = *iPtr++;
					while (count--) {
						*oPtr++ = pixel;
					}
				}
			}
		}
		else {
			fseek(image->file, 512 + (y * image->xsize) + (z * image->xsize * image->ysize),
				SEEK_SET);
			fread(buf, 1, image->xsize, image->file);
		}
	}

	GLubyte* OpenGLFileHandler::read_alpha_texture(const char* name, int* width, int* height)
	{
		unsigned char* base, * lptr;
		ImageRec* image;
		int y;

		image = ImageOpen(name);
		if (!image) {
			return NULL;
		}

		(*width) = image->xsize;
		(*height) = image->ysize;
		if (image->zsize != 1) {
			ImageClose(image);
			return NULL;
		}

		base = (unsigned char*)malloc(image->xsize * image->ysize * sizeof(unsigned char));
		lptr = base;
		for (y = 0; y < image->ysize; y++) {
			ImageGetRow(image, lptr, y, 0);
			lptr += image->xsize;
		}
		ImageClose(image);

		return (unsigned char*)base;
	}

	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
		: width_(width), height_(height)
	{
		internal_format_ = GL_RGBA8;
		data_format_ = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &renderer_id_);
		glTextureStorage2D(renderer_id_, 1, internal_format_, width_, height_);

		glTextureParameteri(renderer_id_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(renderer_id_, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureParameteri(renderer_id_, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(renderer_id_, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		: path_(path), data_format_(), internal_format_(), width_(), height_(), renderer_id_(0)
	{
		if (path.substr(path.size() - 3) == ".bw") {
			ImportFromBWFile(path);
			return;
		}

		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = nullptr;
		{
			//GRT_PROFILE_SCOPE("stbi_load - OpenGLTexture2D::OpenGLTexture2D(const std::string&)");
			data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		}

		if (data)
		{
			is_loaded_ = true;

			width_ = width;
			height_ = height;

			GLenum internalFormat = 0, dataFormat = 0;
			if (channels == 4)
			{
				internalFormat = GL_RGBA8;
				dataFormat = GL_RGBA;
			}
			else if (channels == 3)
			{
				internalFormat = GL_RGB8;
				dataFormat = GL_RGB;
			}

			internal_format_ = internalFormat;
			data_format_ = dataFormat;

			GRT_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");

			glCreateTextures(GL_TEXTURE_2D, 1, &renderer_id_);
			glTextureStorage2D(renderer_id_, 1, internalFormat, width_, height_);

			glTextureParameteri(renderer_id_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTextureParameteri(renderer_id_, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTextureParameteri(renderer_id_, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTextureParameteri(renderer_id_, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTextureSubImage2D(renderer_id_, 0, 0, 0, width_, height_, dataFormat, GL_UNSIGNED_BYTE, data);

			stbi_image_free(data);
		}
		else {
			GRT_CORE_ERROR("stb_image could not load image file! (path='{0}')", path);
		}
	}

	void OpenGLTexture2D::ImportFromBWFile(const std::string& path) {
		GLubyte* imageData;
		int width, height;

		imageData = OpenGLFileHandler::read_alpha_texture(path.c_str(), &width, &height);
		if (imageData == NULL) {
			GRT_CORE_ERROR("Could not load '.bw' image file! (path='{0}')", path);
			return;
		}
			
		glCreateTextures(GL_TEXTURE_2D, 1, &renderer_id_);
		glBindTexture(GL_TEXTURE_2D, renderer_id_);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, width, height, 0,
			GL_LUMINANCE, GL_UNSIGNED_BYTE, imageData);
	
		free(imageData);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &renderer_id_);
	}

	void OpenGLTexture2D::set_data(void* data, uint32_t size)
	{
		uint32_t bpp = data_format_ == GL_RGBA ? 4 : 3;
		GRT_CORE_ASSERT(size == width_ * height_ * bpp, "Data must be entire texture!");
		glTextureSubImage2D(renderer_id_, 0, 0, 0, width_, height_, data_format_, GL_UNSIGNED_BYTE, data);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, renderer_id_);
	}
}