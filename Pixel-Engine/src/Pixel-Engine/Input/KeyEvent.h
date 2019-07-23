#pragma once

#include "../Core.h"
#include "Event.h"

namespace PE
{
	class KeyEvent : public Event
	{
	public:
		inline KeyEvent(EventType type, bool is_pressed, Input key = KEY_UNKNOWN) : Event(type, is_pressed), m_key(key) {}

		// getters
		inline Input getKey() const override { return m_key; }
		
	private:
		Input m_key;
	};

}