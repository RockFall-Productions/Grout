#include "grtpch.h"
#include "Texture.h"

#include "Grout/Renderer/Renderer.h"
#include "Plataform/OpenGL/OpenGLTexture.h"

namespace Grout {
	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::get_api())
		{
		case RendererAPI::API::None:    
										GRT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); 
										return nullptr;
		case RendererAPI::API::OpenGL:  
										return CreateRef<OpenGLTexture2D>(width, height);
		}

		GRT_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::get_api())
		{
		case RendererAPI::API::None:    
										GRT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); 
										return nullptr;
		case RendererAPI::API::OpenGL:  
										return CreateRef<OpenGLTexture2D>(path);
		}

		GRT_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}