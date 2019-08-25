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
		sprite->loadTexture("res/sheet.png");
		sprite->setFrames(12, 8);
		setSprite(sprite);
		setArea();
		setScale(2,2);

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

		addAnimation( getApplication().getAssets().getAnimation("walk_down") );
		addAnimation(walk_left_anim);
		addAnimation(walk_right_anim);
		addAnimation(walk_up_anim);
	}


	inline void recieveSignal(pe::Signal& signal) override {
		print( "[Object1]signal recieved" << signal.getName() );
	}

	inline void input(sf::Event& event) override {}

	inline void process(double dt) override {
		setZIndex( getPosition().y );
		if (pe::isKeyPressed('W')) {
			getAnimation("walk_up").play();
			move(0,-2);
			if (getArea().isIntersecting(npc->getArea())) move(0,2);
		}
		else if (pe::isKeyPressed('A')) {
			getAnimation("walk_left").play();
			move(-2, 0);
			if (getArea().isIntersecting(npc->getArea())) move(2,0);
		}
		else if (pe::isKeyPressed('D')) {
			getAnimation("walk_right").play();
			move(2, 0);
			if (getArea().isIntersecting(npc->getArea())) move(-2,0);
		}
		else if (pe::isKeyPressed('S')) {
			getAnimation("walk_down").play();
			move(0, 2);
			if (getArea().isIntersecting(npc->getArea())) move(0,-2);
		}
		// todo stop any animation

	}

private:
	pe::Object* npc;
};