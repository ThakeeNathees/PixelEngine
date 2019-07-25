#pragma once

#include "../Core.h"
#include "../Math/math.h"
#include "Input.h"

namespace PE
{
	class RenderWindow;
}

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
			MOUSE_PRESSED = BIT(8), MOUSE_RELEASED = BIT(9), MOUSE_WHEEL = BIT(10), MOUSE_MOTION = BIT(11),

			WindowEvent = CLOSED | RESIZED | LOST_FOCUS | GAINED_FOCUSED,
			KeyEvent	= KEY_PRESSED | KEY_RELEASED,
			MouseEvent	= MOUSE_PRESSED | MOUSE_RELEASED | MOUSE_MOTION,
		};

		inline Event(EventType type = Event::NONE) : m_type(type) {}

		// getters
		inline virtual EventType getType() const { return m_type; }
		inline virtual bool istHandled() const { return m_is_handled; }
		virtual std::string toString();

		// setters
		inline virtual void setHandled() { m_is_handled = true; }

		// overrides
		virtual bool isPressed() const;
		virtual Input::Key getKey() const;
		virtual Input::Button getButton() const;
		virtual vec2 getPosition() const;
		virtual vec2 getSize() const;
		virtual float getDelta() const;




	protected:
		friend RenderWindow;
		EventType m_type = NONE ;
		bool m_is_handled = false;
		

		static void convertEvent(std::unique_ptr<Event>& event, void* sfml_event_ptr);
	};
}
