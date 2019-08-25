#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <glm.hpp>

#include "Pixel-Engine.h"

class Npc : public pe::Object
{
	void init() override {

		pe::Sprite* sprite = new pe::Sprite();
		sprite->loadTexture("res/logo.png");
		setSprite(sprite);
		setScale(.15, .15);


		//pe::Area* area = new pe::Area;
		//sf::CircleShape* shape = new sf::CircleShape(225, 6);
		//area->setShape(shape);
		setArea();
	}

	void process(double dt) override {
		setZIndex(getPosition().y);

		auto& a = getScene().getObject("Player").getArea();
		print( getArea().isIntersecting(a) );

		auto mouse = sf::Mouse::getPosition(getApplication().getWindow());

		setPosition(mouse);
	}
};
