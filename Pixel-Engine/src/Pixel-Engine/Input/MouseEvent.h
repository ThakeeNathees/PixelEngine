#pragma once

#include "../Core.h"
#include "Event.h"

namespace PE
{

	class MouseEvent : public Event
	{
	public:
		inline MouseEvent(EventType type, bool is_pressed, Input::Button button, vect2 position = vect2(-1.f, -1.f))
			: Event(type, is_pressed), m_button(button), m_position(position)
		{}

		//getters
		inline Input::Button getButton() const override { return m_button; }
		inline vect2 getPosition() const override { return m_position; }

	private:
		Input::Button m_button;
		vect2 m_position;

	};

}
