#pragma once

#include "Pixel-Engine/Core.h"
#include "Event.h"
#include "Pixel-Engine/Math/math.h"
#include "Input.h"

namespace PE
{

	class MouseEvent : public Event
	{

		inline MouseEvent(EventType type, Input button, vect2 position = vect2(-1.f, -1.f))
			: Event(type), m_button(button), m_position(position)
		{}

		//getters
		inline Input getButton() const { return m_button; }

	private:
		Input m_button;
		vect2 m_position;

	};

}
