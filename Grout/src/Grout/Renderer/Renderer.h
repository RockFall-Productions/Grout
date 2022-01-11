#pragma once

namespace Grout {
	enum class RendererAPI {
		None = 0,
		OpenGL = 1,
		Direct3D = 2,
		Vulkan = 3,
		Metal = 4
	};

	class Renderer {
	public:
		inline static RendererAPI get_api() { return current_api_;  }
	private:
		static RendererAPI current_api_;
	};
}