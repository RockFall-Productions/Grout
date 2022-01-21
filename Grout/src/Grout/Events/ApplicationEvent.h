#pragma once

#include "Event.h"

namespace Grout {
	class  WindowResizeEvent : public Event {
	public:
		// --- Constructor ---
		WindowResizeEvent(uint32_t width, uint32_t height)
		: width_(width), height_(height) {}

		// ----- Getters -----
		inline uint32_t get_width() const { return width_; }
		inline uint32_t get_height() const { return height_; }
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
		uint32_t width_;
		uint32_t height_;
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
		WindowMovedEvent(uint32_t windowX, uint32_t windowY)
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
		uint32_t windowX_;
		uint32_t windowY_;
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