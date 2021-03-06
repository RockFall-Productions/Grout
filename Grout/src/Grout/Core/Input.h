#pragma once

#include "Grout/Core/Core.h"
#include "KeyCodes.h"

namespace Grout {
	// Static class interface that deals with everything related to input
	class  Input {
	public:
		// Calls for implemented IsKeyPressedImpl
		inline static bool is_key_pressed(int keycode) { return instance_->IsKeyPressedImpl(keycode); }

		inline static bool is_mouse_button_pressed(int buttoncode) { return instance_->IsMouseButtonPressedImpl(buttoncode); }
		// Implement custom Vector2
		inline static std::pair<float, float> get_mouse_position() { return instance_->GetMousePositionImpl(); }
		inline static float get_mouse_x() { return instance_->GetMouseXImpl(); }
		inline static float get_mouse_y() { return instance_->GetMouseYImpl(); }

		// Handles mouse
		inline static void set_mouse_pos(float x, float y) { instance_->SetMouseCursorPos(std::make_pair(x, y)); }
		inline static void HideMouseCursor() { instance_->HideMouseCursorImpl(); }
		inline static void ShowMouseCursor() { instance_->ShowMouseCursorImpl(); }
	protected:
		// Returns true if the given key is currently pressed
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(int buttoncode) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

		virtual void HideMouseCursorImpl() = 0;
		virtual void ShowMouseCursorImpl() = 0;
		virtual void SetMouseCursorPos(std::pair<float, float> pos) = 0;
	private:
		static Scope<Input> instance_;
	};
}