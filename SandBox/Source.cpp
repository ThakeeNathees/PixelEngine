// pre-compile this
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <glm.hpp>

#include "Pixel-Engine.h"


class O : public pe::Object{
	
	void init() override {}

	bool input(sf::Event& event) override {
		if (event.type == sf::Event::EventType::KeyPressed) {
			if (event.key.code == 0) {
				setPosition( getPosition() + glm::vec2(-1,0) );
				return true;
			};
			if (event.key.code == 3) {
				setPosition(getPosition() + glm::vec2(1, 0));
			};
		}
		return false;
	}

	void process(double dt) override {
		
	}

};

int main()
{

	O* o = new O();
	pe::Sprite* sp = new pe::Sprite(); sp->loadTexture("res/icon.png");
	o->setSprite(sp); o->setPosition(100, 100);

	//auto oo = new O();
	//pe::Sprite* ss = new pe::Sprite(); ss->loadTexture("res/bg.jpg");
	//ss->setColor(sf::Color(255, 0, 100, 255));
	//oo->setSprite(ss); oo->setPosition(110,110);
	
	pe::Scene* scene = new pe::Scene("scene1");
	scene->addObject(o);
	//scene->addObject(oo);
	scene->sortObjectsZIndex();
	scene->loadBackgroundTexture("res/bg.jpg");

	pe::Application app;
	app.addScene( scene );
	app.setCurrentScene("scene1");
	app.update();
	return 0;
}