#pragma once

#include "../Core.h"
#include "Event.h"

namespace pe
{
	class KeyEvent : public Event
	{
	public:
		inline KeyEvent(EventType type, bool is_pressed, Input::Key key)
			: Event(type), m_is_pressed(is_pressed), m_key(key) {}

		// getters
		inline Input::Key getKey() const override { return m_key; }
		inline bool isPressed() const override { return m_is_pressed; }
	
	private:
		bool m_is_pressed;
		Input::Key m_key;
	};

}