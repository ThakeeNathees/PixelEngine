#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <glm.hpp>

#include "Pixel-Engine.h"

class Object1 : public pe::Object
{
public:
	inline void init() override {
		setName("obj1");
		print("Object1 created");
		pe::Sprite* sp = new pe::Sprite();
		sp->loadTexture("res/logo.png");
		sp->setFrames(2, 2);
		setSprite(sp);
		setArea();
		//setOrigin( getSprite().getLocalBounds().width/2, getSprite().getLocalBounds().height);
		setScale(.15, .15);
		setPosition(100, 100);

		pe::Signal* signal = new pe::Signal("test");
		signal->addReciever(this);
		emitSignal(*signal);

		getApplication().setDebugMode(false);
	}

	inline void draw() const override {
		drawSelf();
	}

	inline void recieveSignal(pe::Signal& signal) override {
		//print( signal.getName() );
	}

	inline void input(sf::Event& event) override {
		getApplication().setEventHandled();
	}

	inline void process(double dt) override {
		time += dt;
		if (0 < time && time < delay) {
			sf::Vector2f pos;
			pos.x = time / delay * pos0.x + (1 - time / delay) * pos1.x;
			pos.y = time / delay * pos0.y + (1 - time / delay) * pos1.y;
			setPosition(pos);
		}

		auto pos = sf::Mouse::getPosition(getApplication().getWindow());


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			rotate(2);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			move(100 * dt, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			scale(1.1, 1.1);
		}
	}

private:
	int ind = 0;
	double time = 0;

	sf::Vector2f pos0 = sf::Vector2f(100, 100);
	sf::Vector2f pos1 = sf::Vector2f(200, 200);
	double delay = 3;


};