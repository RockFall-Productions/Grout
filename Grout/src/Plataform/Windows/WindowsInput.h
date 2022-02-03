#pragma once

#include "Grout/Core/Core.h"
#include "Grout/Core/Input.h"

namespace Grout {
	class WindowsInput : public Input {
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;
		virtual bool IsMouseButtonPressedImpl(int buttoncode) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
		virtual void HideMouseCursorImpl() override;
		virtual void ShowMouseCursorImpl() override;
		virtual void SetMouseCursorPos(std::pair<float, float> pos) override;
	};
}