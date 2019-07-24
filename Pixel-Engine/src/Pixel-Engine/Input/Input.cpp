#include "pepch.h"
#include "Input.h"






namespace PE
{

	bool Input::isKeyPressed(Key key)
	{
		return sf::Keyboard::isKeyPressed(  static_cast<sf::Keyboard::Key>(key) );
	}

	bool Input::isButtonPressed(Button button)
	{
		if (button == BUTTON_UNKNOWN) return false;
		return sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(button));
	}

	//vect2 Input::getMousePosition()

}