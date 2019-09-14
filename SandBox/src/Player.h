#pragma once

#include "Pixel-Engine.h"

class Player : public pe::Object
{
public:
	inline void sceneEntered(pe::Scene* scene) override {
		npc = getScene().getObject("Npc");
	}


	inline void recieveSignal(pe::Signal& signal) override {
		//print( "[player]signal recieved " << signal.getName() << " " << signal.getData().id );
	}

	inline void drawCall() const override {
		drawSelf();
	}

	inline void handleEvent( pe::Event& event) override {}

	inline void process(double dt) override {
		int spd = 10;
		setZindex( getPosition().y );
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			getAnimation("walk_up").play();
			move(0,-2);
			if ( npc && getArea().isIntersecting(npc->getArea())) move(0,2);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			getAnimation("walk_left").play();
			move(-2, 0);
			if (npc && getArea().isIntersecting(npc->getArea())) move(2,0);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			getAnimation("walk_right").play();
			move(2, 0);
			if (npc && getArea().isIntersecting(npc->getArea())) move(-2,0);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			getAnimation("walk_down").play();
			move(0, 2);
			if (npc && getArea().isIntersecting(npc->getArea())) move(0,-2);
		}


	}

private:
	pe::Font* f;
	pe::Object* npc;
};