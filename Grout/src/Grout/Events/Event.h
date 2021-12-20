#pragma once

#include "../Core.h"

#include <string>
#include <functional>

namespace Grout {
	// All Events are implemented in a blocking way:
	// -> Every time an event occurs it is immediately handled
	// TODO: Implement an Event Buffer

	// Every possible event
	enum class EventType 
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	// Used for filtering events
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication	= BIT(0), // Using BIT isntead of normal 0, 1, 2...
		EventCategoryInput			= BIT(1), // makes possible to make an event to be
		EventCategoryKeyboard		= BIT(2), // in multiple categories
		EventCategoryMouse			= BIT(3), // i.e. 26 = 11010 = Input/Mouse/MouseButton
		EventCategoryMouseButton	= BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType getStaticType() {return EventType::##type; }\
							    virtual EventType getStaticType() const override {return getStaticType(); }\
								virtual const har* getName() const override { return #type; }
#define EVENT_CLASS_CATEGORY(category) virtual int getCategoryFlags() const override { return category; } 

	// Pure virtual class of the Event template
	// Must have a type, name and category
	class GROUT_API Event {
		friend class EventDispatcher;
	public:
		// Getters
		virtual EventType getEventType() const = 0;
		virtual const char* getName() const = 0;
		virtual int getCategoryFlags() const = 0;
		virtual std::string ToString() const { return getName(); }

		// Checks if Event category matches the given one
		inline bool isInCategory(EventCategory category) {
			return getCategoryFlags() & category;
		}
	protected:
		// Useful for stopping the propagation of an event
		bool m_Handled = false;
	};

	class EventDispatcher {
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	};

}