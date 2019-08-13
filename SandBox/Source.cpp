// pre-compile this
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <glm.hpp>

#include "Pixel-Engine.h"


class O : public pe::Object{
	
	void init() override {

	}

	void process(double dt) override {
		
	}

};

int main()
{

	O* o = new O();
	pe::Sprite* sp = new pe::Sprite(); sp->loadTexture("res/icon.png");
	o->setSprite(sp); o->setPosition(100, 100);

	O* oo = new O();
	pe::Sprite* ss = new pe::Sprite(); ss->loadTexture("res/icon.png");
	ss->setColor(sf::Color(255, 0, 100, 255));
	oo->setSprite(ss); oo->setPosition(110,110);
	//oo->setZIndex(0);
	
	pe::Scene* scene = new pe::Scene();
	scene->addObject(o);
	scene->addObject(oo);
	scene->sortObjectsZIndex();

	pe::Application app;
	app.addScene( "scene1", scene);
	app.setCurrentScene("scene1");
	app.update();
	return 0;
}