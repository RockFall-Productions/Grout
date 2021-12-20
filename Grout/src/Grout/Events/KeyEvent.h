#pragma once
 
#include "Event.h"

#include <sstream>

namespace Grout {
	class GROUT_API KeyEvent : public Event {
	public:
		// Getter
		inline int getKeyCode() const {
			return m_KeyCode;
		}

		EVENT_CLASS_CATEGORY(EventCategoryApplication | EventCategoryInput)
	protected:
		// Protected constructor
		KeyEvent(int keycode) : m_KeyCode(keycode) {}
		// Holds the ID of the key belonging to this Event
		int m_KeyCode;
	};
}