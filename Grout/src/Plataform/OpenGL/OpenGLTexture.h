#pragma once

#include "Grout/Renderer/Texture.h"

#include <glad/glad.h>

namespace Grout {
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(uint32_t width, uint32_t height);
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual uint32_t get_width() const override { return width_; }
		virtual uint32_t get_height() const override { return height_; }
		virtual uint32_t get_renderer_id() const override { return renderer_id_; }

		virtual void set_data(void* data, uint32_t size) override;

		virtual void Bind(uint32_t slot = 0) const override;

		virtual bool is_loaded() const override { return is_loaded_; }

		virtual bool operator==(const Texture& other) const override
		{
			return renderer_id_ == ((OpenGLTexture2D&)other).renderer_id_;
		}
	private:
		void ImportFromBWFile(const std::string& path);

		std::string path_;
		bool is_loaded_ = false;
		uint32_t width_, height_;
		uint32_t renderer_id_;
		GLenum internal_format_, data_format_;
	};

	class OpenGLFileHandler {
	protected:
		typedef struct _ImageRec {
			unsigned short imagic;
			unsigned short type;
			unsigned short dim;
			unsigned short xsize, ysize, zsize;
			unsigned int min, max;
			unsigned int wasteBytes;
			char name[80];
			unsigned long colorMap;
			FILE* file;
			unsigned char* tmp;
			unsigned long rleEnd;
			unsigned int* rowStart;
			int* rowSize;
		} ImageRec;

		static void ConvertUint(unsigned* array, unsigned int length);
		static void ConvertShort(unsigned short* array, unsigned int length);
		static ImageRec* ImageOpen(const char* fileName);
		static ImageRec* ImageOpenFallback(const char* fileName);
		static void ImageClose(ImageRec* image);
		static GLubyte* read_alpha_texture(const char* name, int* width, int* height);
		static void ImageGetRow(ImageRec* image, unsigned char* buf, int y, int z);

		friend class OpenGLTexture2D;
	};
}

