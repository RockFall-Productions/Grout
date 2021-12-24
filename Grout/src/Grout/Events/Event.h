#pragma once

#include "Grout/Core.h"

#include "grtpch.h"

namespace Grout {
	// All Events are implemented in a blocking way:
	// -> Every time an event occurs it is immediately handled
	// TODO: Implement an Event Buffer

	// Every possible event
	enum class EventType 
	{
		None = 0,
		kWindowClose, kWindowResize, kWindowFocus, kWindowLostFocus, kWindowMoved,
		kAppTicket, kAppUpdate, kAppRender,
		kKeyPressed, kKeyReleased,
		kMouseButtonPressed, kMouseButtonReleased, kMouseMoved, kMouseScrolled
	};

	// Used for filtering events
	enum EventCategory
	{
		kNone = 0,
		kEventCategoryApplication	= BIT(0), // Using BIT(x) instead of normal 0, 1, 2...
		kEventCategoryInput			= BIT(1), // makes it possible to create an event to has
		kEventCategoryKeyboard		= BIT(2), // multiple categories
		kEventCategoryMouse			= BIT(3), // i.e. 26 = 11010 = Input(00010)/Mouse(01000)/MouseButton(10000)
		kEventCategoryMouseButton	= BIT(4)
	};

// Those MACROS are here just for the sake of not needing to
// rewrite the override of getCategory and getType functions
// over and over. Just use EVENT_CLASS_TYPE(type) and it will
// summarize a little bunch of code
//
// The reason we have getStaticType AND getEventType is so, when we
// we have a plain Event class, we can know, through the getEventType(),
// what static event we are dealing with
#define EVENT_CLASS_TYPE(type) static EventType get_static_type() { return EventType::##type; }\
							    virtual EventType get_event_type() const override {return get_static_type(); }\
								virtual const char* get_name() const override { return #type; }
#define EVENT_CLASS_CATEGORY(category) virtual int get_category_flags() const override { return category; } 

	// Pure virtual class of the Event template
	// Must have a type, name and category
	class GROUT_API Event {
		// Friend class so it can access member variables of all events 
		friend class EventDispatcher;
	public:
		// ---- Getters ----
		virtual EventType get_event_type() const = 0; // overrided by GET_CLASS_TYPE
		virtual const char* get_name() const = 0; // overrided by GET_CLASS_TYPE
		virtual int get_category_flags() const = 0; // overrided by GET_CLASS_CATEGORY
		virtual std::string ToString() const { return get_name(); }
		// -----------------

		// Checks if Event category matches the given one
		inline bool IsInCategory(EventCategory category) {
			return get_category_flags() & category;
		}
	protected:
		// Useful for stopping the propagation of an event
		bool is_handled_ = false;
	};

	// Used for resolving any Event
	class EventDispatcher {

		template<typename T>
		// EventFn represents 
		using EventFnc = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			: event_(event) {}

		template<typename T>
		bool Dispatch(EventFnc<T> func) {
			// TODO: Type safety
			// if trying to dispatch an Event of a type that matches this dispatcher
			if (event_.get_event_type() == T::get_static_type()) {
				// We run the given function
				event_.is_handled_ = func(*(T*)&event_);
				return true;
			}
			return false;
		}
	private:
		Event& event_;
	};

	// To easily call ToString() on events
	inline std::ostream& operator<<(std::ostream& os, const Event& e) {
		return os << e.ToString();
	}
}