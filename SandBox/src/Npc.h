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


		pe::Area* area = new pe::Area;
		sf::CircleShape* shape = new sf::CircleShape(225, 6);
		area->setShape(shape);
		setArea(area);
	}

	void process(double dt) override {
		setZIndex(getPosition().y);
		//pe::Area& a1 = getScene().getObject("Player").getArea();
		//auto x = pe::isColliding(a1, getArea());
		//print(x);
		auto mouse = sf::Mouse::getPosition(getApplication().getWindow());
		glm::fvec2 pos;
		pos.x = glm::floor(mouse.x / 32) * 32;
		pos.y = glm::floor(mouse.y / 32) * 32; // grid position

		setPosition(pos);
	}
};
