#pragma once

#include "Event.h"

#include <sstream>

namespace Grout {
	class GROUT_API WindowResizeEvent : public Event {
	public:
		// --- Constructor ---
		WindowResizeEvent(int width, int height) : m_Width(width), m_Height(height) {}

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

	
}