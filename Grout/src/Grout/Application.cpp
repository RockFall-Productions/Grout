#include "grtpch.h"
#include "Application.h"

#include "Grout/Events/Event.h"
#include "Grout/Events/ApplicationEvent.h"
#include "Grout/Log.h"

namespace Grout {
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run() {
		WindowResizeEvent  e(1280, 720);
		GRT_TRACE(e);

		while (true);
	}
}
