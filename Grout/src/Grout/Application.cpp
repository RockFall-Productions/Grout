#include "grtpch.h"
#include "Application.h"

#include <glad/glad.h>

#include "Grout/Input.h"

namespace Grout {
	// Singleton
	// TODO implement it in a correct singleton way
	// https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
	Application* Application::instance_ = nullptr;

	Application::Application()
	{
		GRT_CORE_ASSERT(!instance_, "Trying to create more than one application");
		instance_ = this;

		window_ = std::unique_ptr<Window>(Window::Create());
		window_->set_event_callback(GRT_BIND_EVENT_FN(Application::OnEvent));

		imgui_layer_ = new ImGuiLayer;
		layer_stack_.push_overlay(imgui_layer_);
		imgui_layer_->OnAttach();
	}

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		layer_stack_.push_layer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		layer_stack_.push_overlay(overlay);
		overlay->OnAttach();
	}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(GRT_BIND_EVENT_FN(Application::OnWindowClose));

		// Loops through layer stack from End -> Begin
		for (auto it = layer_stack_.end(); it != layer_stack_.begin(); ) {
			(*--it)->OnEvent(e);
			if (e.is_handled()) {
				break;
			}
		}
	}

	void Application::Run() {
		while (running_) {
			glClearColor(0.3f, 0.3f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			// Loop through all layers
			for (Layer* layer : layer_stack_) {
				layer->OnUpdate();
 			}

			// ----- ImGui Frame flow -----
			imgui_layer_->BeginFrame();

			for (Layer* layer : layer_stack_) {
				layer->OnImGuiRender();
			}

			imgui_layer_->EndFrame();
			// ----------------------------

			window_->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		running_ = false;
		return true;;
	}
}
