#pragma once

#include <sstream>
#include "Event.h"

namespace PE
{
	class PIXEL_ENGINE_API KeyEvent : public Event
	{
	public:
		inline int getKeyCode() const { return m_key_code; }

		// TODO
	protected:
		KeyEvent(int key_code)
			:m_key_code(key_code){}

		int m_key_code;
	};


	class PIXEL_ENGINE_API KeyPressEvent : public KeyEvent
	{
	public :
		KeyPressEvent(int key_code, int repeat_count)
			: KeyEvent(key_code), m_repeat_count(repeat_count){}

		inline int getRepeatCount() const { return m_repeat_count; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "KeyPressEvent: " << m_key_code << " (" << m_repeat_count << " repeats)";
			return ss.str();
		}
		
	private:
		int m_repeat_count;
	};

}
