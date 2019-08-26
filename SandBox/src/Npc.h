#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <glm.hpp>

#include "Pixel-Engine.h"

class Npc : public pe::Object
{
public:
	void init() override {

		pe::Background* bg = new pe::Background();
		pe::Texture* tex = new pe::Texture();
		tex->loadFromFile("res/logo.png");
		bg->setTexture(tex);
		bg->getBgSprite().setScale(.15, .15);
		bg->setRepeatd(true);

		getScene().setBackground(bg);


		pe::Sprite* sprite = new pe::Sprite();
		pe::Texture* texr = new pe::Texture();
		texr->loadFromFile("res/logo.png");
		//sprite->setTexture(texr);
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
		
		//getScene().getBackground().move({1,1});

		f = 1 / dt;
		text.setString(std::to_string(f)+std::string( " fps") );
		//text.setPosition(getPosition() + sf::Vector2f(100,100) );
		setZIndex(getPosition().y);
		auto& player = getScene().getObject("Player").getArea();
		auto mouse = sf::Mouse::getPosition(getApplication().getWindow());
		setPosition(mouse);
	}

private:
	glm::ivec2 off = { 0,0 };
	double f;
	sf::Text text;
	sf::Font font;
};
