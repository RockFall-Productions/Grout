#include "grtpch.h"
#include "VertexArray.h"

#include "Grout/Renderer/Renderer.h"

namespace Grout {
	VertexArray* VertexArray::Create() {
		switch (Renderer::get_api()) {
		case RendererAPI::None:
								GRT_CORE_ASSERT(false, "RendererAPI::None is not supported!");
								return nullptr;
		case RendererAPI::OpenGL:
								return new OpenGLVertexArray();
								break;
		}

		GRT_CORE_ASSERT(false, "Failed to create a VertexArray: The selected RendererAPI is unknown.");
		return nullptr;
	}
}