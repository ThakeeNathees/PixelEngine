#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <glm.hpp>

#include "Pixel-Engine.h"

class Npc : public pe::Object
{
public:
	void init() override {

		pe::Sprite* sprite = pe::Assets::newAsset<pe::Sprite>();
		pe::Texture* texr = pe::Assets::newAsset<pe::Texture>();
		texr->loadFromFile("res/sheet.png");
		sprite->setTexture(*texr);
		sprite->setFrames(12,8);
		setSprite(sprite);
		setScale(2, 2);
		setPosition(200,200);

		
		font.loadFromFile("res/Indie_Flower/IndieFlower-Regular.ttf");
		text.setFont(font);
		text.setString("test");
		text.setCharacterSize(24);
		text.setFillColor(sf::Color(0,0,0,255));

		setOrigin(getSprite().getTextureRect().width / 2, getSprite().getTextureRect().height);
		setArea();

		pe::AssetsWriter w;
		w.addAssets();
		w.save("test.xml");
	}

	void drawCall() const override {
		drawSelf();
		draw( text );
	}

	void process(double dt) override {
		
		//getScene().getBackground().move({1,1});
		//getAnimation("rot").play();

		f = 1 / dt;
		text.setString(std::to_string(f)+std::string( " fps") );
		//text.setPosition(getPosition() + sf::Vector2f(100,100) );
		setZIndex(getPosition().y);
		auto& player = getScene().getObject("player1").getArea();
		auto mouse = sf::Mouse::getPosition(getApplication().getWindow());
		setPosition(mouse);
	}

private:
	glm::ivec2 off = { 0,0 };
	double f;
	sf::Text text;
	sf::Font font;
};
