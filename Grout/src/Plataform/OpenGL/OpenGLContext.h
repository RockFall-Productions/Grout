#pragma once

#include "Grout/Renderer/RendererContext.h"

struct GLFWwindow;

namespace Grout {
	class OpenGLContext : public RendererContext {
	public:
		OpenGLContext(GLFWwindow* window);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* window_;
	};
}