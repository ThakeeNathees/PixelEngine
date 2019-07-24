#pragma once

#include "../Core.h"
#include "Event.h"

namespace PE
{
	class KeyEvent : public Event
	{
	public:
		inline KeyEvent(EventType type, bool is_pressed, Input::Key key = Input::KEY_UNKNOWN) : Event(type, is_pressed), m_key(key) {}

		// getters
		inline Input::Key getKey() const override { return m_key; }
		
	private:
		Input::Key m_key;
	};

}