#pragma once

#include "Grout/Window.h"
#include <GLFW/glfw3.h>

namespace Grout {
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowConfigs& configs);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline int get_width() const override { return data_.width; }
		inline int get_height() const override { return data_.height; }

		// Window Attributes
		inline void set_event_callback(const EventCallbackFn& callback) override { data_.Event_Callback = callback; }
		void set_vsync(bool enabled) override;
		bool is_vsync() const override;

		inline virtual void* get_native_window() const override { return window_;  };
	private:
		virtual void Init(const WindowConfigs& configs);
		virtual void Shutdown();
	private:
		GLFWwindow* window_;

		struct WindowData {
			std::string title;
			int width, height;
			bool vsync;

			EventCallbackFn Event_Callback;
		};

		WindowData data_;
	};

}
