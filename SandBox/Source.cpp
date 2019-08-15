// pre-compile this or move them to pixel-engine.h
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <glm.hpp>

#include "Pixel-Engine.h"


class O : public pe::Object{
	
	void init() override {
		pe::Area* area = new pe::Area();
		auto rect = new sf::RectangleShape( sf::Vector2f(64,64) );
		rect->setFillColor( sf::Color(255, 75, 100, 60) );
		area->setShape( rect );
		setArea( area );
	}

	bool input(sf::Event& event) override {
		if (event.type == sf::Event::EventType::KeyPressed) {
			if (event.key.code == 0) {
				rotate(1);
				return true;
			};
			if (event.key.code == 3) {
				setScale(  getScale().x + .01 ,1 );
			};
		}
		return false;
	}

	void process(double dt) override {}
	

};

int main()
{

	O* o = new O();
	O* oo = new O();
	o->setOrigin(32,32);
	o->setPosition(100,100);


	pe::Sprite* sp = new pe::Sprite(); sp->loadTexture("res/icon.png");
	pe::Sprite* spp = new pe::Sprite(); spp->loadTexture("res/sheet.png");
	(*o).setSprite(sp);
	oo->setSprite(spp);

	pe::Background* bg = new pe::Background();
	//bg->loadTexture("res/bg.jpg");bg->setRepeatd(true);
	
	pe::Scene* scene = new pe::Scene("scene1");
	pe::Scene* scene2 = new pe::Scene("scene2");
	scene->addObject(o);
	scene2->addObject(oo);
	scene->sortObjectsZIndex();
	scene->setBackground(bg);
	

	pe::Application app;
	app.addScene( scene );
	app.addScene( scene2 );
	app.setCurrentScene("scene1");
	app.update();
	return 0;
}