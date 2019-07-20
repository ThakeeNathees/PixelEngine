#pragma once

#include "Pixel-Engine/Core.h"

namespace PE
{
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowLostFocus, WindowMoved,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
	};

	enum EventCategory
	{
		None = 0,
		EventCatogaryInput			= BIT(0),
		EventCatogaryKeyboard		= BIT(1),
		EventCatogaryMouse			= BIT(2),
		EventCatogaryMouseButton	= BIT(3)

	};
	#define EVENT_CLASS_TYPE(type)  static EventType getStaticType() {return EventType::##type;}\
									virtual EventType getEventType() const override { return getStaticTye(); }\
									virtual const char* getName() const override { return #type; }

	class PIXEL_ENGINE_API Event
	{
		// friend class
	public:
		virtual EventType getEventType() const = 0;
		virtual const char* getName() const = 0;
		virtual int getCatogaryFlags() const = 0;
		virtual std::string toString() const { return getName(); }

		inline bool isInCatogary(EventCategory catogary) {
			return getCatogaryFlags() & catogary;
		}
	protected:
		bool m_handled = false;
	};

	
}