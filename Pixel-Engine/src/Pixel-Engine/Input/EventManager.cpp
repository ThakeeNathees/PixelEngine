#include "pepch.h"

#include "EventManager.h"

namespace PE {
	void Event::convertEvent(Event& event, void* sfml_event_ptr)
	{
		sf::Event& sf_event = *((sf::Event*)sfml_event_ptr);
		Input::Key key;
		Input::Button button;
		switch (sf_event.type)
		{
		case sf::Event::Closed:
			event = ::PE::WindowEvent(Event::CLOSED);
			break;
		case sf::Event::Resized:
			event = ::PE::WindowEvent(Event::RESIZED, vec2(sf_event.size.width, sf_event.size.height));
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
			if (sf_event.key.code <= sf::Keyboard::F12)
				key = static_cast<Input::Key>(sf_event.key.code);
			else key = Input::KEY_UNKNOWN;
			event = ::PE::KeyEvent(Event::KEY_PRESSED, true, key);
			break;
		case sf::Event::KeyReleased:
			if (sf_event.key.code <= sf::Keyboard::F12)
				key = static_cast<Input::Key>(sf_event.key.code);
			else key = Input::KEY_UNKNOWN;
			event = ::PE::KeyEvent(Event::KEY_RELEASED, false, key);
			break;

		case sf::Event::MouseButtonPressed:
			if (sf_event.mouseButton.button <= sf::Mouse::Middle)
				button = static_cast<Input::Button>(sf_event.mouseButton.button);
			else button = Input::BUTTON_UNKNOWN;
			event = ::PE::MouseEvent(Event::MOUSE_PRESSED, true, button);
			break;

		case sf::Event::MouseButtonReleased:
			if (sf_event.mouseButton.button <= sf::Mouse::Middle)
				button = static_cast<Input::Button>(sf_event.mouseButton.button);
			else button = Input::BUTTON_UNKNOWN;
			event = ::PE::MouseEvent(Event::MOUSE_RELEASED, false, button);
			break;
		
		case sf::Event::MouseWheelMoved:
			event = ::PE::MouseEvent(Event::MOUSE_WHEEL, false);

			// implement getDelta()

			// TODO: implement reset of this

		}

	}
}