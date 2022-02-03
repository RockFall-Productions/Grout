#include "grtpch.h"
#include "WindowsInput.h"

#include "Grout/Core/Application.h"
#include <GLFW/glfw3.h>

namespace Grout {

	Scope<Input> Input::instance_ = CreateScope<WindowsInput>();

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::get_instance().get_window().get_native_window());
		auto state = glfwGetKey(window, keycode);
		
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	bool WindowsInput::IsMouseButtonPressedImpl(int buttoncode)
	{
		auto window = static_cast<GLFWwindow*>(Application::get_instance().get_window().get_native_window());
		auto state = glfwGetMouseButton(window, buttoncode);
		return state == GLFW_PRESS;
	}
	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::get_instance().get_window().get_native_window());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return { (float)xpos, (float)ypos };
	}
	float WindowsInput::GetMouseXImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return x;
	}
	float WindowsInput::GetMouseYImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return y;
	}
}