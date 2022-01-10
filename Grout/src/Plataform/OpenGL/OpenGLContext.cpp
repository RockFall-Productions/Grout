#include "grtpch.h"
#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Grout {
	OpenGLContext::OpenGLContext(GLFWwindow* window) : window_(window)
	{
		GRT_CORE_ASSERT(window != NULL, "The window given to OpenGLContext is NULL")
	}
	void OpenGLContext::Init()
	{
		// Tells GLFW that window_ is where the current context must be
		glfwMakeContextCurrent(window_);
		// Load Glad
		int glad_loaded = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		GRT_CORE_ASSERT(glad_loaded, "Failed to initialize Glad!");


		GRT_CORE_INFO("OpenGL Info:");
		GRT_CORE_INFO("	 Vendor:   {0}", glGetString(GL_VENDOR));
		GRT_CORE_INFO("	 Renderer: {0}", glGetString(GL_RENDERER));
		GRT_CORE_INFO("	 Version:  {0}", glGetString(GL_VERSION));

	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(window_);
	}
}