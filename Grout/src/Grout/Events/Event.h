#pragma once

#include "Grout/Core.h"

namespace Grout {
	// All Events are implemented in a blocking way:
	// -> Every time an event occurs it is immediately handled
	// TODO: Implement an Event Buffer

	// Every possible event
	enum class EventType 
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTicket, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	// Used for filtering events
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication	= BIT(0), // Using BIT(x) instead of normal 0, 1, 2...
		EventCategoryInput			= BIT(1), // makes it possible to create an event to has
		EventCategoryKeyboard		= BIT(2), // multiple categories
		EventCategoryMouse			= BIT(3), // i.e. 26 = 11010 = Input(00010)/Mouse(01000)/MouseButton(10000)
		EventCategoryMouseButton	= BIT(4)
	};

// Those MACROS are here just for the sake of not needing to
// rewrite the override of getCategory and getType functions
// over and over. Just use EVENT_CLASS_TYPE(type) and it will
// summarize a little bunch of code
//
// The reason we have getStaticType AND getEventType is so, when we
// we have a plain Event class, we can know, through the getEventType(),
// what static event we are dealing with
#define EVENT_CLASS_TYPE(type) static EventType getStaticType() {return EventType::##type; }\
							    virtual EventType getEventType() const override {return getStaticType(); }\
								virtual const char* getName() const override { return #type; }
#define EVENT_CLASS_CATEGORY(category) virtual int getCategoryFlags() const override { return category; } 

	// Pure virtual class of the Event template
	// Must have a type, name and category
	class GROUT_API Event {
		// Friend class so it can access member variables of all events 
		friend class EventDispatcher;
	public:
		// ---- Getters ----
		virtual EventType getEventType() const = 0; // overrided by GET_CLASS_TYPE
		virtual const char* getName() const = 0; // overrided by GET_CLASS_TYPE
		virtual int getCategoryFlags() const = 0; // overrided by GET_CLASS_CATEGORY
		virtual std::string ToString() const { return getName(); }
		// -----------------

		// Checks if Event category matches the given one
		inline bool isInCategory(EventCategory category) {
			return getCategoryFlags() & category;
		}
	protected:
		// Useful for stopping the propagation of an event
		bool m_Handled = false;
	};

	// Used for resolving any Event
	class EventDispatcher {

		template<typename T>
		// EventFn represents 
		using EventFnc = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			: m_Event(event) {}

		template<typename T>
		bool Dispatch(EventFnc<T> func) {
			// TODO: Type safety
			// if trying to dispatch an Event of a type that matches this dispatcher
			if (m_Event.getEventType() == T::GetStaticType()) {
				// We run the given function
				m_Event.m_Handled = func(*(T*)) & m_Event;
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	// To easily call ToString() on events
	inline std::ostream& operator<<(std::ostream& os, const Event& e) {
		return os << e.ToString();
	}
}