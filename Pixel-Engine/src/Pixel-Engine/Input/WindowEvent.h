#pragma once

#include "../Core.h"
#include "Event.h"

namespace pe
{
	class WindowEvent : public Event
	{
	public:

		inline WindowEvent(EventType type, vec2 size = vec2(-1.f,-1.f))
			: Event(type), m_size(size)
		{}

		inline virtual vec2 getSize() const override {
			if (m_type == RESIZED)
				return m_size;
			return getSizeError();
		}

	private:
		vec2 m_size;
		vec2 getSizeError() const;

	};

}