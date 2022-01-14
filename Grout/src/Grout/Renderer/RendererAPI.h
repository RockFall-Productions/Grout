#pragma once

#include <glm/glm.hpp>
#include "VertexArray.h"

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
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertex_array) = 0;

		inline static API get_api() { return api_; };
	private:
		static API api_;
	};
}

