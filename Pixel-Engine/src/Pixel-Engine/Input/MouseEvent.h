#pragma once

#include "../Core.h"
#include "Event.h"

namespace PE
{

	class MouseEvent : public Event
	{
	public:
		inline MouseEvent(EventType type, bool is_pressed, vect2 position, Input::Button button = Input::BUTTON_UNKNOWN)
			: Event(type), m_is_pressed(is_pressed), m_button(button), m_position(position)
		{}

		//getters
		inline Input::Button getButton() const override { return m_button; }
		inline vect2 getPosition() const override { return m_position; }
		inline bool isPressed() const override { return m_is_pressed; }

	private:
		bool m_is_pressed;
		Input::Button m_button;
		vect2 m_position;

	};

}
