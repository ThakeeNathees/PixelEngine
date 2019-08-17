#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <glm.hpp>

#include "Pixel-Engine.h"

class Object1 : public pe::Object
{
public:
	inline void init() override {
		pe::Sprite* sp = new pe::Sprite();
		sp->loadTexture( "res/logo.png" );
		setSprite(sp);
		setScale(.15);
		setArea();
		getScene().setDebugMode(true);
	}
	
	inline void process(double dt) override {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			move( 10, 0 );
		}
	}

};