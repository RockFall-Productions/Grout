#pragma once

#include "Event.h"

namespace Grout {
	class GROUT_API MouseMovedEvent : public Event {
	public:
		// --- Constructor ---
		MouseMovedEvent(float x, float y)
			: mouseX_(x), mouseY_(y) {}
		// ----- Getters -----
		inline float get_x() const { return mouseX_; }
		inline float get_y() const { return mouseY_; }
		// -------------------

		// Debug default ToString()
		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseMovedEvent: " << mouseX_ << ", " << mouseY_;
			return ss.str();
		}

		EVENT_CLASS_TYPE(kMouseMoved)
		EVENT_CLASS_CATEGORY(kEventCategoryMouse | kEventCategoryInput)

	private:
		// Position on the screen
		float mouseX_;
		float mouseY_;
	};

	class GROUT_API MouseScrolledEvent : public Event {
	public:
		// --- Constructor ---
		MouseScrolledEvent(float x_offset, float y_offset)
			: x_offset_(x_offset), y_offset_(y_offset) {}
		// ----- Getters -----
		inline float get_x_offset() const { return x_offset_; }
		inline float get_y_offset() const { return y_offset_; }
		// -------------------

		// Debug default ToString()
		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << x_offset_ << ", " << y_offset_;
			return ss.str();
		}

		EVENT_CLASS_TYPE(kMouseScrolled)
		EVENT_CLASS_CATEGORY(kEventCategoryMouse | kEventCategoryInput)

	private:
		// Position on the screen
		float x_offset_;
		float y_offset_;
	};

	class GROUT_API MouseButtonEvent : public Event {
	public:
		inline int getMouseButtonCode() const { return buttom_code_; }

		EVENT_CLASS_CATEGORY(kEventCategoryMouseButton | kEventCategoryMouse | kEventCategoryInput)
	protected:
		// Protectate constructor so it cannot be instantiated
		MouseButtonEvent(int buttom_code)
			: buttom_code_(buttom_code) {}
		// Holds the ID of the buttom belonging to this Event
		int buttom_code_;
	};

	class GROUT_API MouseButtonPressedEvent : public MouseButtonEvent {
	public:
		// --- Constructor ---
		MouseButtonPressedEvent(int buttom_code)
			: MouseButtonEvent(buttom_code) {}

		// Debug default ToString()
		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << buttom_code_;
			return ss.str();
		}

		EVENT_CLASS_TYPE(kMouseButtonPressed)
	};

	class GROUT_API MouseButtonReleasedEvent : public MouseButtonEvent {
	public:
		// --- Constructor ---
		MouseButtonReleasedEvent(int buttom_code)
			: MouseButtonEvent(buttom_code) {}

		// Debug default ToString()
		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << buttom_code_;
			return ss.str();
		}

		EVENT_CLASS_TYPE(kMouseButtonReleased)
	};
}