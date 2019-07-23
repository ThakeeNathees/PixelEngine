#pragma once

#include "../Core.h"
#include "../Math/math.h"
#include "Input.h"

namespace PE
{
	class PIXEL_ENGINE_API Event
	{
	public:
		enum EventType
		{
			NONE = 0,
			CLOSED = BIT(0), RESIZED = BIT(1), LOST_FOCUS = BIT(2), GAINED_FOCUSED = BIT(3),
			MOUSE_ENTERED = BIT(4), MOUSE_LEFT = BIT(5),
			KEY_PRESSED = BIT(6), KEY_RELEASED = BIT(7),
			MOUSE_BUTTON_PRESSED = BIT(8), MOUSE_BUTTON_RELEASED = BIT(9), MOUSE_WHEEL = BIT(10), MOUSE_MOTION = BIT(11),

			WindowEvent = CLOSED | RESIZED | LOST_FOCUS | GAINED_FOCUSED,
			KeyEvent	= KEY_PRESSED | KEY_RELEASED,
			MouseEvent	= MOUSE_BUTTON_PRESSED | MOUSE_BUTTON_RELEASED | MOUSE_MOTION,
		};
		inline Event(EventType type, bool is_pressed) : m_type(type), m_is_pressed(is_pressed), m_is_handled(false) {}

		// getters
		inline virtual EventType getType() const { return m_type; }
		inline virtual bool getHandled() const { return m_is_handled; }
		inline virtual bool isPressed() const { return m_is_pressed; }

		// setters
		inline virtual void setHandled(bool is_handled) { m_is_handled = is_handled; }

		// overrides
		virtual inline Input getKey() const;
		virtual inline Input getButton() const;
		virtual inline vect2 getPosition() const;

	protected:
		EventType m_type = NONE ;
		bool m_is_handled;
		bool m_is_pressed;
		


	};
}
