#pragma once

#include "Event.h"

#include <sstream>

namespace Grout {
	class GROUT_API MouseMovedEvent : public Event {
	public:
		// --- Constructor ---
		MouseMovedEvent(float x, float y)
			: m_MouseX(x), m_MouseY(y) {}
		// ----- Getters -----
		inline float getX() const { return m_MouseX; }
		inline float getY() const { return m_MouseY; }
		// -------------------

		// Debug default ToString()
		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		// Position on the screen
		float m_MouseX;
		float m_MouseY;
	};

	class GROUT_API MouseScrolledEvent : public Event {
	public:
		// --- Constructor ---
		MouseScrolledEvent(float xOffset, float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {}
		// ----- Getters -----
		inline float getXOffset() const { return m_XOffset; }
		inline float getYOffset() const { return m_YOffset; }
		// -------------------

		// Debug default ToString()
		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << m_XOffset << ", " << m_YOffset;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		// Position on the screen
		float m_XOffset;
		float m_YOffset;
	};

	class GROUT_API MouseButtonEvent : public Event {
	public:
		inline int getMouseButtonCode() const { return m_ButtonCode; }

		EVENT_CLASS_CATEGORY(EventCategoryMouseButton | EventCategoryMouse | EventCategoryInput)
	protected:
		// Protectate constructor so it cannot be instantiated
		MouseButtonEvent(int buttomCode)
			: m_ButtonCode(buttomCode) {}
		// Holds the ID of the buttom belonging to this Event
		int m_ButtonCode;
	};

	class GROUT_API MouseButtonPressedEvent : public MouseButtonEvent {
	public:
		// --- Constructor ---
		MouseButtonPressedEvent(int buttomCode)
			: MouseButtonEvent(buttomCode) {}

		// Debug default ToString()
		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_ButtonCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class GROUT_API MouseButtonReleasedEvent : public MouseButtonEvent {
	public:
		// --- Constructor ---
		MouseButtonReleasedEvent(int buttomCode)
			: MouseButtonEvent(buttomCode) {}

		// Debug default ToString()
		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_ButtonCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}