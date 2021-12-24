#include "grtpch.h"
#include "Application.h"

#include <GLFW/glfw3.h>

namespace Grout {

// Wraps a function to be passed as a parameter - currently used for the callbacks
// TODO: change the location of this
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
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		GRT_CORE_TRACE("{0}", e);
	}

	void Application::Run() {
		while (running_) {
			glClearColor(0.3, 0.3, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			window_->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		running_ = false;
		return true;;
	}
}
