#pragma once

#include "Pixel-Engine/Core.h"
#include "Event.h"
#include "Input.h"

namespace PE
{
	class KeyEvent : public Event
	{
		inline KeyEvent(EventType type, Input key = KEY_NONE) : Event(type), m_key(key) {}

		// getters
		inline Input getKey() const { return m_key; }
		
	private:
		Input m_key;
	};

}