#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"

namespace Grout {
	class GROUT_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	private:
		std::unique_ptr<Window> window_;
		bool running_ = true;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}

