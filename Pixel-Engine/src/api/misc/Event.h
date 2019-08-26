#pragma once
#include "..//core.h"

namespace pe
{
	class PIXEL_ENGINE_API Event : public sf::Event
	{
	public:
		inline void setHandled() {
			m_is_handled = true;
		}
		inline bool isHandled() const {
			return m_is_handled;
		}
	private:
		bool m_is_handled = false;
	};
}