#include "grtpch.h"
#include "RenderCommand.h"

#include "Plataform/OpenGL/OpenGLRendererAPI.h"

namespace Grout {
	Scope<RendererAPI> RenderCommand::renderer_api_ = CreateScope<OpenGLRendererAPI>();
}