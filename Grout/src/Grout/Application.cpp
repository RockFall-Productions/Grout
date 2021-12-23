#include "grtpch.h"
#include "Application.h"

#include "Grout/Events/ApplicationEvent.h"
#include "Grout/Log.h"

namespace Grout {
	Application::Application()
	{
		window_ = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{
	}

	void Application::Run() {
		while (running_) {
			window_->OnUpdate();
		}
	}
}
