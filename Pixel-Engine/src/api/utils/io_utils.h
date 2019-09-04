#pragma once
#include "../core.h"

// TODO: up_key, down_key, numpad, delete, control, shift and other

namespace pe
{
	inline bool isKeyPressed(char key) {
		switch (key)
		{
		case 'A': return sf::Keyboard::isKeyPressed(sf::Keyboard::A);
		case 'B': return sf::Keyboard::isKeyPressed(sf::Keyboard::B);
		case 'C': return sf::Keyboard::isKeyPressed(sf::Keyboard::C);
		case 'D': return sf::Keyboard::isKeyPressed(sf::Keyboard::D);
		case 'E': return sf::Keyboard::isKeyPressed(sf::Keyboard::E);
		case 'F': return sf::Keyboard::isKeyPressed(sf::Keyboard::F);
		case 'G': return sf::Keyboard::isKeyPressed(sf::Keyboard::G);
		case 'H': return sf::Keyboard::isKeyPressed(sf::Keyboard::H);
		case 'I': return sf::Keyboard::isKeyPressed(sf::Keyboard::I);
		case 'J': return sf::Keyboard::isKeyPressed(sf::Keyboard::J);
		case 'K': return sf::Keyboard::isKeyPressed(sf::Keyboard::K);
		case 'L': return sf::Keyboard::isKeyPressed(sf::Keyboard::L);
		case 'M': return sf::Keyboard::isKeyPressed(sf::Keyboard::M);
		case 'N': return sf::Keyboard::isKeyPressed(sf::Keyboard::N);
		case 'O': return sf::Keyboard::isKeyPressed(sf::Keyboard::O);
		case 'P': return sf::Keyboard::isKeyPressed(sf::Keyboard::P);
		case 'Q': return sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
		case 'R': return sf::Keyboard::isKeyPressed(sf::Keyboard::R);
		case 'S': return sf::Keyboard::isKeyPressed(sf::Keyboard::S);
		case 'T': return sf::Keyboard::isKeyPressed(sf::Keyboard::T);
		case 'U': return sf::Keyboard::isKeyPressed(sf::Keyboard::U);
		case 'V': return sf::Keyboard::isKeyPressed(sf::Keyboard::V);
		case 'W': return sf::Keyboard::isKeyPressed(sf::Keyboard::W);
		case 'X': return sf::Keyboard::isKeyPressed(sf::Keyboard::X);
		case 'Y': return sf::Keyboard::isKeyPressed(sf::Keyboard::Y);
		case 'Z': return sf::Keyboard::isKeyPressed(sf::Keyboard::Z);
		}
		return false;
	}
}