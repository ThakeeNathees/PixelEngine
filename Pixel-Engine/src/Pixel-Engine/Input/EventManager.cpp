#include "pepch.h"

#include "EventManager.h"

namespace PE {
	void Event::convertEvent(Event& event, void* sfml_event_ptr)
	{
		sf::Event& sf_event = *((sf::Event*)sfml_event_ptr);

		switch (sf_event.type)
		{
		case sf::Event::Closed:
			event = ::PE::WindowEvent(Event::CLOSED);
			break;
		case sf::Event::Resized:
			event = ::PE::WindowEvent(Event::RESIZED, vect2(sf_event.size.width, sf_event.size.height));
			break;
		case sf::Event::LostFocus:
			event = ::PE::WindowEvent(Event::LOST_FOCUS);
			break;
		case sf::Event::GainedFocus:
			event = ::PE::WindowEvent(Event::GAINED_FOCUSED);
			break;
		case sf::Event::MouseEntered:
			event = ::PE::WindowEvent(Event::MOUSE_ENTERED);
			break;
		case sf::Event::MouseLeft:
			event = ::PE::WindowEvent(Event::MOUSE_LEFT);
			break;

		case sf::Event::KeyPressed:
			Input::Key key;
			if (sf_event.key.code <= sf::Keyboard::F12)
				key = static_cast<Input::Key>(sf_event.key.code);
			else key = Input::KEY_UNKNOWN;
			event = ::PE::KeyEvent(Event::KEY_PRESSED, true, key);
			break;

			// TODO: implement reset of this

		}

	}
}