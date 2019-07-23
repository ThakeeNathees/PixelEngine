#pragma once
#include "Pixel-Engine/Core.h"

namespace PE
{
	class PIXEL_ENGINE_API Event
	{
	public:
		enum EventType
		{
			NONE = -1,
			CLOSED, RESIZED, LOST_FOCUS, GAINED_FOCUSED, MOUSE_ENTERED, MOUSE_LEFT, 
			KEY_PRESSED, KEY_RELEASED, 
			MOUSE_BUTTON_PRESSED, MOUSE_BUTTON_RELEASED, MOUSE_WHEEL, MOUSE_MOVED, 
		};
		inline Event(EventType type) : m_type(type) {}

		// getters
		inline virtual EventType getType() const { return m_type; }
		inline virtual bool getHandled() const { return m_is_handled; }

		// setters
		inline virtual void setHandled(bool is_handled) { m_is_handled = is_handled; }

	protected:
		EventType m_type = NONE ;
		bool m_is_handled;
		


	};
}
