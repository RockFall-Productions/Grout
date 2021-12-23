#include "grtpch.h"
#include "WindowsWindow.h"

#include "Grout/Log.h"

namespace Grout {

	static bool has_glfw_initialized = false;

	// Plataform specific function from Window class
	Window* Window::Create(const WindowConfigs& configs) {
		return new WindowsWindow(configs);
	}

	WindowsWindow::WindowsWindow(const WindowConfigs& configs)
	{
		Init(configs);
	}

	WindowsWindow::~WindowsWindow()
	{
		// We may change this due to multiple windows
		Shutdown();
	}

	void WindowsWindow::Init(const WindowConfigs& configs)
	{
		// Setting up WindowData
		data_.title = configs.title;
		data_.width = configs.width;
		data_.height = configs.height;

		GRT_INFO("Creating window {0} ({1}, {2})", configs.title, configs.width, configs.height);
		// Starts GLFW
		if (!has_glfw_initialized) {
			int success = glfwInit();
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			GRT_CORE_ASSERT(sucess, "Could not initialize GLFW!");

			has_glfw_initialized = true;
		}

		window_ = glfwCreateWindow(configs.width, configs.height, data_.title.c_str(), nullptr, nullptr);

		if (window_ == NULL) {
			GRT_CORE_ASSERT(false, "Failed to create GLFW window");
		}

		glfwMakeContextCurrent(window_);
		// Used mainly to connect the callback and event system to GLFW
		glfwSetWindowUserPointer(window_, &data_);
		set_vsync(true);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(window_);
	}

	void WindowsWindow::set_vsync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
		data_.vsync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return data_.vsync;
	}



	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(window_);
	}
}