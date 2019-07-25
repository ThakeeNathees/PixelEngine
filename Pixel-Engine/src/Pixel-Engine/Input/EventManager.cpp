#include "pepch.h"

#include "EventManager.h"

namespace pe {
	void Event::convertEvent(std::unique_ptr<Event>& event, void* sfml_event_ptr)
	{
		sf::Event& sf_event = *((sf::Event*)sfml_event_ptr);
		Input::Key key;
		Input::Button button;
		switch (sf_event.type)
		{
		case sf::Event::Closed:
			event = std::make_unique<::pe::WindowEvent>(Event::CLOSED);
			break;
		case sf::Event::Resized:
			event = std::make_unique <::pe::WindowEvent>(Event::RESIZED, vec2(sf_event.size.width, sf_event.size.height));
			break;
		case sf::Event::LostFocus:
			event = std::make_unique <::pe::WindowEvent>(Event::LOST_FOCUS);
			break;
		case sf::Event::GainedFocus:
			event = std::make_unique <::pe::WindowEvent>(Event::GAINED_FOCUSED);
			break;
		case sf::Event::MouseEntered:
			event = std::make_unique <::pe::WindowEvent>(Event::MOUSE_ENTERED);
			break;
		case sf::Event::MouseLeft:
			event = std::make_unique <::pe::WindowEvent>(Event::MOUSE_LEFT);
			break;

		case sf::Event::KeyPressed:
			if (sf_event.key.code <= sf::Keyboard::F12)
				key = static_cast<Input::Key>(sf_event.key.code);
			else key = Input::KEY_UNKNOWN;
			event = std::make_unique <::pe::KeyEvent>(Event::KEY_PRESSED, true, key);
			break;
		case sf::Event::KeyReleased:
			if (sf_event.key.code <= sf::Keyboard::F12)
				key = static_cast<Input::Key>(sf_event.key.code);
			else key = Input::KEY_UNKNOWN;
			event = std::make_unique <::pe::KeyEvent>(Event::KEY_RELEASED, false, key);
			break;

		case sf::Event::MouseButtonPressed:
			if (sf_event.mouseButton.button <= sf::Mouse::Middle)
				button = static_cast<Input::Button>(sf_event.mouseButton.button);
			else button = Input::BUTTON_UNKNOWN;
			event = std::make_unique <::pe::MouseEvent>(Event::MOUSE_PRESSED, true, button);
			break;

		case sf::Event::MouseButtonReleased:
			if (sf_event.mouseButton.button <= sf::Mouse::Middle)
				button = static_cast<Input::Button>(sf_event.mouseButton.button);
			else button = Input::BUTTON_UNKNOWN;
			event = std::make_unique <::pe::MouseEvent>(Event::MOUSE_RELEASED, false, button);
			break;
		
		case sf::Event::MouseWheelMoved:
			event = std::make_unique <::pe::MouseEvent>(Event::MOUSE_WHEEL, false, Input::BUTTON_UNKNOWN, vec2(-1.f,-1.f), sf_event.mouseWheel.delta);
			break;

		case sf::Event::MouseMoved:
			event = std::make_unique <::pe::MouseEvent>(Event::MOUSE_MOTION, false, Input::BUTTON_UNKNOWN,  vec2(sf_event.mouseMove.x, sf_event.mouseMove.y));
			break;

		}

	}
}