#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <glm.hpp>

#include "Pixel-Engine.h"

class Npc : public pe::Object
{
public:
	void init() override {

		pe::Sprite* sprite = new pe::Sprite();
		sprite->loadTexture("res/logo.png");
		setSprite(sprite);
		setScale(.15, .15);

		
		font.loadFromFile("res/Indie_Flower/IndieFlower-Regular.ttf");
		text.setFont(font);
		text.setString("test");
		text.setCharacterSize(24);
		text.setFillColor(sf::Color(0,0,0,255));

		setArea();
	}

	void drawCall() const override {
		drawSelf();
		draw( text );
	}

	void process(double dt) override {
		f = 1 / dt;
		text.setString(std::to_string(f)+std::string( " fps") );
		//text.setPosition(getPosition() + sf::Vector2f(100,100) );
		setZIndex(getPosition().y);
		auto& player = getScene().getObject("Player").getArea();
		auto mouse = sf::Mouse::getPosition(getApplication().getWindow());
		setPosition(mouse);
	}

private:
	double f;
	sf::Text text;
	sf::Font font;
};
