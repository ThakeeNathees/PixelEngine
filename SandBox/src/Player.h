#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <glm.hpp>

#include "Pixel-Engine.h"

class Player : public pe::Object
{
public:
	inline void init() override {
		npc = getScene().getObject("Npc");
	}


	inline void recieveSignal(pe::Signal& signal) override {
		print( "[player]signal recieved " << signal.getName() << " " << signal.getData().id );
	}

	inline void drawCall() const override {
		drawSelf();
	}

	inline void input( pe::Event& event) override {}

	inline void process(double dt) override {
		int spd = 10;
		setZIndex( getPosition().y );
		if (pe::isKeyPressed('W')) {
			getApplication().setCurrentScene(70001);
			getAnimation("walk_up").play();
			move(0,-2);
			if ( npc && getArea().isIntersecting(npc->getArea())) move(0,2);
		}
		else if (pe::isKeyPressed('A')) {
			getAnimation("walk_left").play();
			move(-2, 0);
			if (npc && getArea().isIntersecting(npc->getArea())) move(2,0);
		}
		else if (pe::isKeyPressed('D')) {
			getAnimation("walk_right").play();
			move(2, 0);
			if (npc && getArea().isIntersecting(npc->getArea())) move(-2,0);
		}
		else if (pe::isKeyPressed('S')) {
			getAnimation("walk_down").play();
			move(0, 2);
			if (npc && getArea().isIntersecting(npc->getArea())) move(0,-2);
		}
		// todo stop any animation

	}

private:
	pe::Font* f;
	pe::Object* npc;
};