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

		// Function that will be passed to window as a callbackfn 
		void OnEvent(Event& e);
	private:
		// Current window
		std::unique_ptr<Window> window_;
		bool running_ = true;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}

