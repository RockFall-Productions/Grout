#pragma once
 
#include "Event.h"

#include <sstream>

namespace Grout {
	// A class to be derived from only
	// Set's the keyCode member and Event category
	class GROUT_API KeyEvent : public Event {
	public:
		// Getter
		inline int getKeyCode() const { return m_KeyCode; }

		// This overrides getCategoryFlags to return the correct category
		EVENT_CLASS_CATEGORY(EventCategoryApplication | EventCategoryInput)
	protected:
		// Protected constructor so it can't be constructed
		KeyEvent(int keycode) : m_KeyCode(keycode) {}
		// Holds the ID of the key belonging to this Event
		int m_KeyCode;
	};


	class GROUT_API KeyPressedEvent : public KeyEvent {
	public:
		// --- Constructor ---
		KeyPressedEvent(int keyCode, int repeatCount) 
			: KeyEvent(keyCode), m_RepeatCount(repeatCount) {}

		// ----- Getters -----
		inline int getRepeatCount() const { return m_RepeatCount; }
		// -------------------

		// Debug default ToString()
		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	protected:
		int m_RepeatCount;
	};

	class GROUT_API KeyReleasedEvent : public KeyEvent {
	public:
		// ---- Costructor ----
		KeyReleasedEvent(int keycode) 
			: KeyEvent(keycode) {}

		// Debug default ToString()
		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};
}