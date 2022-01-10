#pragma once

#include "Event.h"

namespace Grout {
	class  WindowResizeEvent : public Event {
	public:
		// --- Constructor ---
		WindowResizeEvent(int width, int height) 
		: width_(width), height_(height) {}

		// ----- Getters -----
		inline int get_width() const { return width_; }
		inline int get_height() const { return height_; }
		// --------------------

		// Debug default ToString()
		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowResizeEvent: " << width_ << ", " << height_;
			return ss.str();
		}

		// Those override parent's functions to return the
		// correspondent type and category
		EVENT_CLASS_TYPE(kWindowResize)
		EVENT_CLASS_CATEGORY(kEventCategoryApplication)

	private:
		// Size in pixels of the window
		int width_;
		int height_;
	};

	class  WindowCloseEvent : public Event {
	public:
		WindowCloseEvent() {}

		// Debug default ToString()
		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowClosedEvent";
			return ss.str();
		}

		EVENT_CLASS_TYPE(kWindowClose)
		EVENT_CLASS_CATEGORY(kEventCategoryApplication)
	};

	class  WindowMovedEvent : public Event {
	public:
		// ---- Constructor ----
		WindowMovedEvent(int windowX, int windowY)
			: windowX_(windowX), windowY_(windowY) {}

		// Debug default ToString()
		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowMovedEvent: " << windowX_ << ", " << windowY_;
			return ss.str();
		}

		EVENT_CLASS_TYPE(kWindowMoved)
		EVENT_CLASS_CATEGORY(kEventCategoryApplication)
	private:
		// New position data
		int windowX_;
		int windowY_;
	};

	class  AppTicketEvent : public Event {
	public:
		AppTicketEvent() {}

		EVENT_CLASS_TYPE(kAppTicket)
		EVENT_CLASS_CATEGORY(kEventCategoryApplication)
	};

	class  AppUpdateEvent : public Event {
	public:
		AppUpdateEvent() {}

		EVENT_CLASS_TYPE(kAppUpdate)
		EVENT_CLASS_CATEGORY(kEventCategoryApplication)
	};

	class  AppRenderEvent : public Event {
	public:
		AppRenderEvent() {}

		EVENT_CLASS_TYPE(kAppRender)
		EVENT_CLASS_CATEGORY(kEventCategoryApplication)
	};
}