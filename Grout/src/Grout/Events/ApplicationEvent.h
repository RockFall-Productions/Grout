#pragma once

#include "Event.h"

namespace Grout {
	class GROUT_API WindowResizeEvent : public Event {
	public:
		WindowResizeEvent(int width, int height) : m_Width(width), m_Height(height) {}


	};
}