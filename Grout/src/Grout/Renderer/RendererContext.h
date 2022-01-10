#pragma once

namespace Grout {

	// Must be inherited by a specific renderer (i.e. OpenGL or Vulcan)
	// Is responsible for all plataform rendering specific functions
	class RendererContext {
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;

	private:
	};
}