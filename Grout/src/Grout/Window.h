#pragma once

#include "grtpch.h"

#include "Grout/Core.h"
#include "Grout/Events/Event.h"

namespace Grout {

	// Holds title and size data
	struct WindowConfigs {
		std::string title;
		int width;
		int height;

		WindowConfigs(const std::string& title = "Grout Engine",
						int width = 1280,
						int height = 720)
					: title(title), width(width), height(height) { }
	};

	// Interface for a general desktop Window
	// 
	// Needs the following information:
	//	Size: Width, height
	//	VSync: bool
	//	Event_callback: std::function
	class GROUT_API Window {
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		// Getters
		virtual int get_width() const = 0;
		virtual int get_height() const = 0;

		// Setters
		virtual void set_event_callback(const EventCallbackFn& callback) = 0;
		virtual void set_vsync(bool enabled) = 0;

		virtual bool is_vsync() const = 0;

		// This garantees the windows (whatever it is) is accessible
		virtual void* get_native_window() const = 0;

		// Implemented by plataform
		static Window* Create(const WindowConfigs& configs = WindowConfigs());
	};

}