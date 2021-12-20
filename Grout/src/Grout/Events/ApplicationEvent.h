#pragma once

#include "Event.h"

#include <sstream>

namespace Grout {
	class GROUT_API WindowResizeEvent : public Event {
	public:
		// --- Constructor ---
		WindowResizeEvent(int width, int height) 
		: m_Width(width), m_Height(height) {}

		// ----- Getters -----
		inline int getWidth() const { return m_Width; }
		inline int getHeight() const { return m_Height; }
		// --------------------

		// Debug default ToString()
		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		// Those override parent's functions to return the
		// correspondent type and category
		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:
		// Size in pixels of the window
		int m_Width;
		int m_Height;
	};

	class GROUT_API WindowCloseEvent : public Event {
	public:
		WindowCloseEvent() {}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class GROUT_API WindowMovedEvent : public Event {
	public:
		// ---- Constructor ----
		WindowMovedEvent(int windowX, int windowY)
			: m_WindowX(windowX), m_WindowY(windowY) {}

		// Debug default ToString()
		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowMovedEvent: " << m_WindowX << ", " << m_WindowY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowMoved)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
		// New position data
		int m_WindowX;
		int m_WindowY;
	};

	class GROUT_API AppTicketEvent : public Event {
	public:
		AppTicketEvent() {}

		EVENT_CLASS_TYPE(AppTicket)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class GROUT_API AppUpdateEvent : public Event {
	public:
		AppUpdateEvent() {}

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class GROUT_API AppRenderEvent : public Event {
	public:
		AppRenderEvent() {}

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}