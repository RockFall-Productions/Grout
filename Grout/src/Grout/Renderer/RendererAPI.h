#pragma once

#include <glm/glm.hpp>
#include "VertexArray.h"

#include "Grout/Core/Macros.h"

namespace Grout {
	class RendererAPI
	{
	public:
		enum class API {
			None = 0,
			OpenGL = 1,
			Direct3D = 2,
			Vulkan = 3,
			Metal = 4
		};

	public:
		virtual void Init() = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;


		virtual void SetDepthFunc(GRTenum type) = 0;

		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertex_array) = 0;

		virtual void CreateCubeMap(uint32_t* cubemap_texture, std::string* faces_cubemap) = 0;

		inline static API get_api() { return api_; };
	private:
		static API api_;
	};
}

