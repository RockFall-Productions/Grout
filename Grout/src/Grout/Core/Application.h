#pragma once

#include "Core.h"

#include "Grout/Core/Window.h"
#include "Grout/Core/LayerStack.h"
#include "Grout/ImGui/ImGuiLayer.h"

#include "Grout/Events/Event.h"
#include "Grout/Events/ApplicationEvent.h"

#include "Grout/Core/Time.h"

namespace Grout {
	class  Application
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

		inline static Application& get_instance() { return *instance_; };
		inline Window& get_window() const { return *window_;  }
	private:
		// Event handling functions
		bool OnWindowClose(WindowCloseEvent& e);
	private:
		// Current context
		std::unique_ptr<Window> window_;
		bool running_ = true;

		// Layer Stack
		LayerStack layer_stack_;
		ImGuiLayer* imgui_layer_;
	private:
		// Singleton
		static Application* instance_;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}

