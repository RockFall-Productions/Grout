#include "grtpch.h"
#include "Buffer.h"

#include "RendererAPI.h"
#include "Plataform/OpenGL/OpenGLBuffer.h"

namespace Grout {
	//////////////////////////// VERTEX BUFFER ///////////////////////////
	VertexBuffer* VertexBuffer::Create(void* vertices, uint32_t size)
	{
		switch (RendererAPI::get_api()) {
		case RendererAPI::API::None:
								GRT_CORE_ASSERT(false, "RendererAPI::None is not supported!");
								return nullptr;
		case RendererAPI::API::OpenGL:
								return new OpenGLVertexBuffer(vertices, size);
								break;
		}

		GRT_CORE_ASSERT(false, "Failed to create a VertexBuffer: The selected RendererAPI is unknown.");
		return nullptr;
	}

	//////////////////////////// INDEX BUFFER ////////////////////////////
	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (RendererAPI::get_api()) {
		case RendererAPI::API::None:
								GRT_CORE_ASSERT(false, "RendererAPI::None is not supported!");
								return nullptr;
		case RendererAPI::API::OpenGL:
								return new OpenGLIndexBuffer(indices, size);
								break;
		}

		GRT_CORE_ASSERT(false, "Failed to create a VertexBuffer: The selected RendererAPI is unknown.");
		return nullptr;
	}
}