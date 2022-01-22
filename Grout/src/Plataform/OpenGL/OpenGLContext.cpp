#include "grtpch.h"
#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Grout {
	OpenGLContext::OpenGLContext(GLFWwindow* window) : window_(window)
	{
		GRT_CORE_ASSERT(window != NULL, "The window given to OpenGLContext is NULL");
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

#ifdef GRT_ENABLE_ASSERTS
		int versionMajor;
		int versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

		GRT_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Hazel requires at least OpenGL version 4.5!");
#endif
	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(window_);
	}
}