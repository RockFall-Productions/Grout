#pragma once

namespace Grout {

	// Available shader's data types supported by Grout renderer API
	enum class ShaderDataType {
		None = 0,
		Float, Float2, Float3, Float4,
		Int, Int2, Int3, Int4,
		Mat3, Mat4,
		Bool
	};

	// Returns the size of given data type
	static uint32_t ShaderDataTypeSize(ShaderDataType type) {

		switch (type)
		{
		case Grout::ShaderDataType::None:	return 0;
		case Grout::ShaderDataType::Float:	return 4;
		case Grout::ShaderDataType::Float2:	return 4 * 2;
		case Grout::ShaderDataType::Float3:	return 4 * 3;
		case Grout::ShaderDataType::Float4:	return 4 * 4;
		case Grout::ShaderDataType::Int:	return 4;
		case Grout::ShaderDataType::Int2:	return 4 * 2;
		case Grout::ShaderDataType::Int3:	return 4 * 3;
		case Grout::ShaderDataType::Int4:	return 4 * 4;
		case Grout::ShaderDataType::Mat3:	return 4 * 3 * 3;
		case Grout::ShaderDataType::Mat4:	return 4 * 4 * 4;
		case Grout::ShaderDataType::Bool:	return 1;
		}

		GRT_CORE_ASSERT(false, "ShaderDataTypeSize - The given type {0} is unknown", static_cast<int>(type));
		return 0;
	}

	// Holds useful data of a Buffer
	struct BufferElement {
		std::string name;
		ShaderDataType type;
		uint32_t size;
		uint32_t offset;
		// used when the data coming in need some sort of treatment 
		// (i.e. uint32_t -> float)
		bool normalized;

		BufferElement() : name(), type(ShaderDataType::None), size(0), offset(0), normalized(false)  {}

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: name(name), type(type), size(ShaderDataTypeSize(type)), offset(0), normalized(normalized)
		{ 

		}

		// Returns the number of individual components per type
		uint32_t get_component_count() const {
			switch (type)
			{
				case Grout::ShaderDataType::None:	return 0;
				case Grout::ShaderDataType::Float:	return 1;
				case Grout::ShaderDataType::Float2:	return 2;
				case Grout::ShaderDataType::Float3:	return 3;
				case Grout::ShaderDataType::Float4:	return 4;
				case Grout::ShaderDataType::Int:	return 1;
				case Grout::ShaderDataType::Int2:	return 2;
				case Grout::ShaderDataType::Int3:	return 3;
				case Grout::ShaderDataType::Int4:	return 4;
				case Grout::ShaderDataType::Mat3:	return 3 * 3;
				case Grout::ShaderDataType::Mat4:	return 4 * 4;
				case Grout::ShaderDataType::Bool:	return 1;
			}

			GRT_CORE_ASSERT(false, "BufferElement::get_component_count - The given type {0} is unknown", static_cast<int>(type));
			return 0;
		}
	};

	// Hold's the data that decribes how the buffer should be interpreted
	// Used when assigning a Vertex Buffer to a Vertex Array Object (VAO)
	class BufferLayout {
	public:
		BufferLayout() {}

		BufferLayout(const std::initializer_list<BufferElement>& elements) 
		: elements_(elements) {
			CalculateOffsetAndStride();
		}

		inline const std::vector<BufferElement>& get_elements() const { return elements_; }
		inline const uint32_t get_stride() const { return stride_; }

		std::vector<BufferElement>::iterator begin() { return elements_.begin(); }
		std::vector<BufferElement>::iterator end() { return elements_.end(); }

		std::vector<BufferElement>::const_iterator begin() const { return elements_.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return elements_.end(); }

	private:
		// Calculates and sets the size of each offset for each element
		// Also calculates the Stride os parent Buffer
		void CalculateOffsetAndStride() {
			uint32_t offset = 0;
			this->stride_ = 0;

			for (auto& element : elements_) {
				element.offset = offset;
				offset += ShaderDataTypeSize(element.type);
				stride_ += ShaderDataTypeSize(element.type);
			}
		}
	private:
		std::vector<BufferElement> elements_;
		uint32_t stride_ = 0;
	};


	// Pure virtual interface to be implemented for each graphic's API
	class VertexBuffer {
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const BufferLayout& get_layout() const = 0;
		virtual void set_layout(const BufferLayout& layout) = 0;

		static VertexBuffer* Create(void* vertices, uint32_t size);
	};

	// Pure virtual interface to be implemented for each graphic's API
	class IndexBuffer {
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t get_count() const = 0;

		static IndexBuffer* Create(uint32_t* indices, uint32_t size);
	};
}


