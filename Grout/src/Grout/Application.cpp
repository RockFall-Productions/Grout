#include "grtpch.h"
#include "Application.h"

#include "Grout/Events/ApplicationEvent.h"

#include <GLFW/glfw3.h>

namespace Grout {

// Wraps a function to be passed as a parameter - used for the callbacks
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application::Application()
	{
		window_ = std::unique_ptr<Window>(Window::Create());
		window_->set_event_callback(BIND_EVENT_FN(Application::OnEvent));
	}

	Application::~Application()
	{
	}

	void Application::OnEvent(Event& e) {
		GRT_CORE_INFO("{0}", e);
	}

	void Application::Run() {
		while (running_) {
			glClearColor(1, 0, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			window_->OnUpdate();
		}
	}
}
