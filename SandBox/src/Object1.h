#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <glm.hpp>

#include "Pixel-Engine.h"

class Object1 : public pe::Object
{
public:
	inline void init() override {
		print("Object1 created");
		pe::Sprite* sp = new pe::Sprite();
		sp->loadTexture( "res/logo.png" );
		setSprite(sp);
		setArea();
		setOrigin( getSprite().getLocalBounds().width/2, getSprite().getLocalBounds().height / 2);
		setScale(.15);
		setPosition(100,100);
		getScene().setDebugMode(true);
	}
	
	/*inline void draw(sf::RenderTarget& target) const {
		if (hasSprite() ) target.draw( getSprite() );

	}*/

	inline void process(double dt) override {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			rotate(2);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			move(10,0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			scale( 1.1, .9 );
		}
	}

};