#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <glm.hpp>

#include "Pixel-Engine.h"

class Player : public pe::Object
{
public:
	inline void init() override {

		pe::Sprite* sprite = new pe::Sprite();
		pe::Texture* tex = new pe::Texture();
		tex->loadFromFile("res/sheet.png");
		sprite->setTexture(tex);
		sprite->setFrames(12, 8);
		setSprite(sprite);

		//*
		pe::Area* area = new pe::Area();
		sf::ConvexShape* shape = new sf::ConvexShape(4);
		shape->setPoint(0, {0,0});
		shape->setPoint(1, {48,0});
		shape->setPoint(2, {60,60});
		shape->setPoint(3, {0,48});
		area->setShape(shape);
		setArea(area);
		//*/
		setPosition(100,100);
		setScale(2,2);

		setOrigin( getSprite().getTextureRect().width/2, getSprite().getTextureRect().height );

		npc = &getScene().getObject("Npc");

		pe::Animation* walk_down_anim = new pe::Animation("walk_down"); walk_down_anim->setTimeLength(.4);
		pe::Animation* walk_left_anim = new pe::Animation("walk_left"); walk_left_anim->setTimeLength(.4);
		pe::Animation* walk_right_anim = new pe::Animation("walk_right"); walk_right_anim->setTimeLength(.4);
		pe::Animation* walk_up_anim = new pe::Animation("walk_up"); walk_up_anim->setTimeLength(.4);

		pe::SpriteFrameTrack* walk_down_track = new pe::SpriteFrameTrack();
		walk_down_track->addKey({.0,0});
		walk_down_track->addKey({.1,1});
		walk_down_track->addKey({.2,2});
		walk_down_track->addKey({.3,1});
		walk_down_anim->setSpriteFrameTrack(walk_down_track);

		pe::SpriteFrameTrack* walk_left_track = new pe::SpriteFrameTrack();
		walk_left_track->addKey({ .0,12 });
		walk_left_track->addKey({ .1,13 });
		walk_left_track->addKey({ .2,14 });
		walk_left_track->addKey({ .3,13 });
		walk_left_anim->setSpriteFrameTrack(walk_left_track);

		pe::SpriteFrameTrack* walk_right_track = new pe::SpriteFrameTrack();
		walk_right_track->addKey({ .0,24 });
		walk_right_track->addKey({ .1,25 });
		walk_right_track->addKey({ .2,26 });
		walk_right_track->addKey({ .3,25 });
		walk_right_anim->setSpriteFrameTrack(walk_right_track);

		pe::SpriteFrameTrack* walk_up_track = new pe::SpriteFrameTrack();
		walk_up_track->addKey({ .0,36 });
		walk_up_track->addKey({ .1,37 });
		walk_up_track->addKey({ .2,38 });
		walk_up_track->addKey({ .3,37 });
		walk_up_anim->setSpriteFrameTrack(walk_up_track);

		getApplication().getAssets().addAnimation(walk_down_anim);

		addAnimation(getApplication().getAssets().getAnimation("walk_down") );
		addAnimation(walk_left_anim);
		addAnimation(walk_right_anim);
		addAnimation(walk_up_anim);

		text.setString("testing");
		text.setCharacterSize(60);

		pe::Texture* texe = new pe::Texture();
		texe->loadFromFile("res/logo.png");

		pe::Background* bg = new pe::Background();
		bg->setTexture(texe);
		bg->setMoveSpeed({300,0});
		bg->setRepeatd(true);
		bg->setScale(.15,.15);
		getScene().setBackground(bg);

		test( this, bg, texe );
	}


	inline void recieveSignal(pe::Signal& signal) override {
		print( "[Object1]signal recieved" << signal.getName() );
	}

	inline void drawCall() const override {
		drawSelf();
	}

	inline void input( pe::Event& event) override {}

	inline void process(double dt) override {
		int spd = 10;
		setZIndex( getPosition().y );
		if (pe::isKeyPressed('W')) {
			getAnimation("walk_up").play();
			//getApplication().getWindow().setPosition( getApplication().getWindow().getPosition() + sf::Vector2i(0,-spd) );
			move(0,-2);
			if (getArea().isIntersecting(npc->getArea())) move(0,2);
		}
		else if (pe::isKeyPressed('A')) {
			getAnimation("walk_left").play();
			//getApplication().getWindow().setPosition( getApplication().getWindow().getPosition() + sf::Vector2i(-spd,0) );
			move(-2, 0);
			if (getArea().isIntersecting(npc->getArea())) move(2,0);
		}
		else if (pe::isKeyPressed('D')) {
			getAnimation("walk_right").play();
			//getApplication().getWindow().setPosition( getApplication().getWindow().getPosition() + sf::Vector2i(spd,0) );
			move(2, 0);
			if (getArea().isIntersecting(npc->getArea())) move(-2,0);
		}
		else if (pe::isKeyPressed('S')) {
			getAnimation("walk_down").play();
			//getApplication().getWindow().setPosition( getApplication().getWindow().getPosition() + sf::Vector2i(0, spd) );
			move(0, 2);
			if (getArea().isIntersecting(npc->getArea())) move(0,-2);
		}
		// todo stop any animation

	}

private:
	sf::Text text;
	pe::Font* f;
	pe::Object* npc;
};