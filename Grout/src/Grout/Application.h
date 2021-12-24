#pragma once

#include "Core.h"

#include "Grout/Window.h"
#include "Grout/LayerStack.h"

#include "Grout/Events/Event.h"
#include "Grout/Events/ApplicationEvent.h"

namespace Grout {
	class GROUT_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		// Deals with layers
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		// Function that will be passed to window as a callbackfn 
		void OnEvent(Event& e);
	private:
		// Event handling functions
		bool OnWindowClose(WindowCloseEvent& e);

		// Current window
		std::unique_ptr<Window> window_;
		bool running_ = true;

		// Layer Stack
		LayerStack layer_stack_;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}

