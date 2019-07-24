#pragma once

#include "../Core.h"
#include "Event.h"

namespace PE
{
	class WindowEvent : public Event
	{
	public:

		inline WindowEvent(EventType type, vect2 size = vect2(-1.f,-1.f))
			: Event(type, false)
		{}

		inline virtual vect2 getSize() const override {
			if (m_type == RESIZED)
				return m_size;
			return getSizeError();
		}

	private:
		vect2 getSizeError() const;

	protected:
		vect2 m_size;

	};

}