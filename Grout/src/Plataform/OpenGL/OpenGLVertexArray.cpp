#include "grtpch.h"
#include "OpenGLVertexArray.h"

namespace Grout {
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
		switch (type)
		{
			case Grout::ShaderDataType::None:	return GL_NONE;
			case Grout::ShaderDataType::Float:	return GL_FLOAT;
			case Grout::ShaderDataType::Float2:	return GL_FLOAT;
			case Grout::ShaderDataType::Float3:	return GL_FLOAT;
			case Grout::ShaderDataType::Float4:	return GL_FLOAT;
			case Grout::ShaderDataType::Int:	return GL_INT;
			case Grout::ShaderDataType::Int2:	return GL_INT;
			case Grout::ShaderDataType::Int3:	return GL_INT;
			case Grout::ShaderDataType::Int4:	return GL_INT;
			case Grout::ShaderDataType::Mat3:	return GL_FLOAT;
			case Grout::ShaderDataType::Mat4:	return GL_FLOAT;
			case Grout::ShaderDataType::Bool:	return GL_BOOL;
		}

		GRT_CORE_ASSERT(false, "ShaderDataTypeToOpenGLBaseType - The given type {0} is unknown", type);
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray() : id_(0) {
		glGenVertexArrays(1, &id_);
		glBindVertexArray(id_);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &id_);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(id_);
	}
	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}
	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertex_buffer)
	{
		glBindVertexArray(id_);
		vertex_buffer->Bind();

		GRT_CORE_ASSERT(vertex_buffer->get_layout().get_elements().size(), "Adding a VertexBuffer to the VertexArray without a layout");

		uint32_t index = 0;
		const auto& layout = vertex_buffer->get_layout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index,
				element.get_component_count(),
				ShaderDataTypeToOpenGLBaseType(element.type),
				element.normalized ? GL_TRUE : GL_FALSE,
				vertex_buffer->get_layout().get_stride(),
				(const void*)element.offset
			);
			++index;
		}

		vertex_buffers_.push_back(vertex_buffer);
	}
	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& index_buffer)
	{
		glBindVertexArray(id_);
		index_buffer->Bind();

		index_buffer_ = index_buffer;
	}
}