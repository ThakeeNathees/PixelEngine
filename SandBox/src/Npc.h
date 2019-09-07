#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <glm.hpp>

#include "Pixel-Engine.h"

class Npc : public pe::Object
{
public:
	void init() override {
		font.loadFromFile("res/Indie_Flower/IndieFlower-Regular.ttf");
		text.setFont(font);
		setArea();
	}

	void drawCall() const override {
		drawSelf();
		draw( text );
	}

	void process(double dt) override {
		setZIndex(getPosition().y);
		auto mouse = sf::Mouse::getPosition(getApplication().getWindow());
		setPosition(sf::Vector2f(mouse.x, mouse.y));
	}

private:
	glm::ivec2 off = { 0,0 };
	double f;
	sf::Text text;
	sf::Font font;
};
