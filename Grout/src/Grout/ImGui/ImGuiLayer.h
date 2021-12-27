#pragma once

#include "Grout/Layer.h"
#include "Grout/Events/MouseEvent.h"
#include "Grout/Events/KeyEvent.h"
#include "Grout/Events/ApplicationEvent.h"

namespace Grout {
	class GROUT_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();

		void OnUpdate();
		void OnEvent(Event& event);
	private:
		// Callback functions
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);

		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);

		bool OnWindowResizedEvent(WindowResizeEvent& e);
		bool OnWindowClosedEvent(WindowCloseEvent& e);

	private:
		float time_ = 0.0f;
	};
}

