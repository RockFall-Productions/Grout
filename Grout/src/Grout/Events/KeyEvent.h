#pragma once
 
#include "Event.h"

namespace Grout {
	// A class to be derived from only
	// Set's the keyCode member and Event category
	class GROUT_API KeyEvent : public Event {
	public:
		// Getter
		inline int get_key_code() const { return key_code_; }

		// This overrides getCategoryFlags to return the correct category
		EVENT_CLASS_CATEGORY(kEventCategoryApplication | kEventCategoryInput)

	protected:
		// Protected constructor so it can't be constructed
		KeyEvent(int keycode) : key_code_(keycode) {}
		// Holds the ID of the key belonging to this Event
		int key_code_;
	};


	class GROUT_API KeyPressedEvent : public KeyEvent {
	public:
		// --- Constructor ---
		KeyPressedEvent(int keyCode, int repeatCount) 
			: KeyEvent(keyCode), repeated_count_(repeatCount) {}

		// ----- Getters -----
		inline int get_repeated_count() const { return repeated_count_; }
		// -------------------

		// Debug default ToString()
		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent: " << key_code_ << " (" << repeated_count_ << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(kKeyPressed)
	protected:
		int repeated_count_;
	};

	class GROUT_API KeyReleasedEvent : public KeyEvent {
	public:
		// ---- Costructor ----
		KeyReleasedEvent(int keycode) 
			: KeyEvent(keycode) {}

		// Debug default ToString()
		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << key_code_;
			return ss.str();
		}

		EVENT_CLASS_TYPE(kKeyReleased)
	};
}