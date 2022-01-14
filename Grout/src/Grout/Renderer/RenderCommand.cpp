#include "grtpch.h"
#include "RenderCommand.h"

#include "Plataform/OpenGL/OpenGLRendererAPI.h"

namespace Grout {
	RendererAPI* RenderCommand::renderer_api_ = new OpenGLRendererAPI();
}