#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <glm.hpp>

#include "Pixel-Engine.h"

class Object1 : public pe::Object
{
public:
	inline void init() override {
		setName( "obj1" );
		print("Object1 created");
		pe::Sprite* sp = new pe::Sprite();
		sp->loadTexture( "res/logo.png" );
		setSprite(sp);
		setArea();
		setOrigin( getSprite().getLocalBounds().width/2, getSprite().getLocalBounds().height / 2);
		setScale(.15);
		setPosition(100,100);

		pe::Signal* signal = new pe::Signal("test");
		signal->addReciever(this);

		emitSignal(*signal);


		//getScene().setDebugMode(true);
	}
	
	inline void draw() const override {
		drawSelf();
	}

	inline void recieveSignal(const pe::Signal& signal) {
		print( signal.getName() );
		
	}

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