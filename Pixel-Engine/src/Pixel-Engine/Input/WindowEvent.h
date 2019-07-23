#pragma once

#include "../Core.h"
#include "Event.h"

namespace PE
{
	class WindowEvent : public Event
	{
	public:

		inline WindowEvent(EventType type)
			: Event(type, false)
		{}

	};

}