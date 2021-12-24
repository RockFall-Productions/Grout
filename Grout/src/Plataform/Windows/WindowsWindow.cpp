#include "grtpch.h"
#include "WindowsWindow.h"

#include "Grout/Events/ApplicationEvent.h"
#include "Grout/Events/MouseEvent.h"
#include "Grout/Events/KeyEvent.h"

#include "glad/glad.h"

namespace Grout {

	static bool has_glfw_initialized = false;

	static void GLFWErrorCallback(int error, const char* description) {
		GRT_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	// Plataform specific function from Window class
	Window* Window::Create(const WindowConfigs& configs) {
		// Check for possible memory leak?
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

		// Starts GLFW if not yet
		if (!has_glfw_initialized) {
			// Initializes GLFW
			int success = glfwInit();
			// Specify the client API version (in this case OpenGL 3.3) that 
			// the created window must be compatible with
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			// From 'Core Profile' (Mordern functions) or 'Compatibility Profile' (Modern + Outdated)
			// - Using CORE PROFILE
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			// Makes sure it has initialized successfully
			GRT_CORE_ASSERT(sucess, "Could not initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);

			has_glfw_initialized = true;
		}

		window_ = glfwCreateWindow(configs.width, configs.height, data_.title.c_str(), nullptr, nullptr);

		if (window_ == NULL) {
			GRT_CORE_ASSERT(false, "Failed to create GLFW window");
		}

		// Tells GLFW that window_ is where the current context must be
		glfwMakeContextCurrent(window_);
		// Load Glad
		int glad_loaded = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		GRT_CORE_ASSERT(glad_loaded, "Failed to initialize Glad!")
		// Used mainly to connect the callback and event system to GLFW
		glfwSetWindowUserPointer(window_, &data_);
		set_vsync(true);


		// -------------	SETTING GLFW CALLBACKS   -----------------------
		glfwSetWindowSizeCallback(window_, [](GLFWwindow* window, int new_width, int new_height)
		{
			// Getting the WindowData refere that was store into UserPointer
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.width = new_width;
			data.height = new_height;
			// Calling event callback
			WindowResizeEvent event(new_width, new_height);
			data.Event_Callback(event);
		});

		glfwSetWindowCloseCallback(window_, [](GLFWwindow* window)
		{
			// Getting the WindowData refere that was store into UserPointer
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.Event_Callback(event);
		});

		glfwSetKeyCallback(window_, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			// Getting the WindowData refere that was store into UserPointer
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
				case GLFW_PRESS: {
					KeyPressedEvent event(key, 0);
					data.Event_Callback(event);
					break;
				}
				case GLFW_RELEASE: {
					KeyReleasedEvent event(key);
					data.Event_Callback(event);
					break;
				}
				case GLFW_REPEAT: {
					KeyPressedEvent event(key, 1);
					data.Event_Callback(event);
					break;
				}
			}
		});

		glfwSetMouseButtonCallback(window_, [](GLFWwindow* window, int button, int action, int mods)
		{
			// Getting the WindowData refere that was store into UserPointer
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
				case GLFW_PRESS: {
					MouseButtonPressedEvent event(button);
					data.Event_Callback(event);
					break;
				}
				case GLFW_RELEASE: {
					MouseButtonReleasedEvent event(button);
					data.Event_Callback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(window_, [](GLFWwindow* window, double x_offset, double y_offset)
		{
			// Getting the WindowData refere that was store into UserPointer
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)x_offset, (float)y_offset);
			data.Event_Callback(event);
		});

		glfwSetCursorPosCallback(window_, [](GLFWwindow* window, double xpos, double ypos)
		{
			// Getting the WindowData refere that was store into UserPointer
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xpos, (float)ypos);
			data.Event_Callback(event);
		});
		//glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
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