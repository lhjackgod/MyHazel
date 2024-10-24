#pragma once
#include "Hazel/Events/Event.h"
namespace Hazel {
	class HAZEL_API WindowResizeEvent : public Event {
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			:m_Width(width), m_Height(height){}
		unsigned int GetWidth() const { return m_Width; }
		unsigned int GetHeight() const { return m_Height; }
		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << "," << m_Height;
			return ss.str();
		}
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		EVENT_CLASS_TYPE(WindowResize)
	private:
		int m_Width, m_Height;
	};
	class HAZEL_API WindowCloseEvent : public Event {
	public:
		WindowCloseEvent() = default;
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		EVENT_CLASS_TYPE(WindowClose)
	};
	class AppTickEvent : Event {
	public:
		AppTickEvent() = default;
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		EVENT_CLASS_TYPE(AppTick)
	};
	class HAZEL_API AppUpdateEvent : Event {
	public:
		AppUpdateEvent() = default;
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		EVENT_CLASS_TYPE(AppUpdate)
	};
	class HAZEL_API AppRenderEvent : Event {
	public:
		AppRenderEvent() = default;
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		EVENT_CLASS_TYPE(AppRender)
	};
}