#include "grtpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Plataform/OpenGL/OpenGLShader.h"

namespace Grout {
	Shader* Shader::Create(const char* vertex_code, const char* fragment_code, const char* geometry_code) {
		switch (Renderer::get_api()) {
		case RendererAPI::API::None:	
										GRT_CORE_ASSERT(false, "RendererAPI::None is not supported!"); 
										return nullptr;
		case RendererAPI::API::OpenGL:  
										return new OpenGLShader(vertex_code, fragment_code, geometry_code);
		}

		GRT_CORE_ASSERT(false, "Failed to create Shader: The selected RendererAPI is unknown.");
		return nullptr;
	}
	Shader* Shader::Create(const std::string& file_path)
	{
		switch (Renderer::get_api()) {
		case RendererAPI::API::None:
										GRT_CORE_ASSERT(false, "RendererAPI::None is not supported!");
										return nullptr;
		case RendererAPI::API::OpenGL:
										return new OpenGLShader(file_path);
		}

		GRT_CORE_ASSERT(false, "Failed to create Shader: The selected RendererAPI is unknown.");
		return nullptr;
	}
}