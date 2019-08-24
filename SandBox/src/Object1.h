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
		getApplication().setDebugMode(false);
		pe::Sprite* sp = new pe::Sprite();
		sp->loadTexture("res/sheet.png");
		sp->setFrames(12, 8);
		setSprite(sp);
		setArea();
		setOrigin( getSprite().getLocalBounds().width/2, getSprite().getLocalBounds().height);
		//getApplication().setDebugMode(true);
		setScale(2.f);
		setPosition(100, 100);

		//pe::Timer* timer = new pe::Timer("test timer",1, true);
		//timer->setSignalReciever(this);
		//addTimer(timer);

		pe::Animation* anim = new pe::Animation("anim");
		anim->setTimeLength(3);
		anim->getAnimEndSignal().addReciever(this);
		anim->setLoop(false);
		//anim->setReverse(true);
		pe::SpriteFrameTrack* spf = new pe::SpriteFrameTrack();
		spf->addKey({ 0, 0 });
		spf->addKey({ .1, 1 });
		spf->addKey({ .2, 2 });
		spf->addKey({ .3, 1 });
		//anim->setSpriteFrameTrack(spf);

		//anim->setRelative(false);
		//setPosition(0,0);

		pe::PositionTrack* pt = new pe::PositionTrack();
		pe::Track::Data d;
		d.position = glm::fvec2(0,0);
		pt->addKey({ 0, d });
		d.position = glm::fvec2(100, 100);
		pt->addKey({ 3, d });
		anim->setPositionTrack(pt);

		setRotation(90);
		pe::RotationTrack* rt = new pe::RotationTrack();
		d.rotation = 0;
		rt->addKey({0,d});
		d.rotation = 90;
		rt->addKey({3,d});
		anim->setRotationTrack(rt);

		pe::ScaleTrack* st = new pe::ScaleTrack();
		d.scale = glm::fvec2(1,1);
		st->addKey({0,d});
		d.scale = glm::fvec2(2,3);
		st->addKey({3,d});
		anim->setScaleTrack(st);


		addAnimation(anim);

		pe::Timer* t = new pe::Timer("new timer",2, true);
		addTimer(t);
		//t->setSignalReciever(this);
		getTimer("new timer").start();

	}

	inline void draw() const override {
		drawSelf();
	}

	inline void recieveSignal(pe::Signal& signal) override {
		print( signal.getName() );
	}

	inline void input(sf::Event& event) override {
		getApplication().setEventHandled();
	}

	inline void process(double dt) override {
		
		getAnimation("anim").play();


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