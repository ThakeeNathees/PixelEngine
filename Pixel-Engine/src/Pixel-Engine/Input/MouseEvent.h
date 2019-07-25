#pragma once

#include "../Core.h"
#include "Event.h"

namespace PE
{

	class MouseEvent : public Event
	{
	public:
		inline MouseEvent(EventType type, bool is_pressed, Input::Button button = Input::BUTTON_UNKNOWN, vec2 position = vec2(-1.f, -1.f))
			: Event(type), m_is_pressed(is_pressed), m_button(button), m_position(position)
		{}

		//getters
		inline Input::Button getButton() const override { return m_button; }
		inline bool isPressed() const override { return m_is_pressed; }
		inline vec2 getPosition() const override {
			if (m_type == Event::MOUSE_MOTION)
				return m_position;
			return getPositionError();
		}

	private:
		vec2 getPositionError() const;
		bool m_is_pressed;
		Input::Button m_button;
		vec2 m_position;
		bool m_delta; // for mouse wheel scrolled

	};

}
