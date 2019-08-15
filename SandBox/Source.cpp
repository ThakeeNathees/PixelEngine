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
		setScale(2, 1);
		setPosition(200, 100);
		setRotation(45);

		
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

	void process(double dt) override {
		auto app = getApplication();
		auto pos = sf::Mouse::getPosition( *app->getWindow() );
		
		//print(  ( (getArea()->isContains(pos) )?"inside":"outside" )  );
	}

	void draw(sf::RenderTarget& target) const override {
		target.draw(*getSprite());
		sf::CircleShape s(100, 2);
		s.setFillColor({ 100, 30, 80, 200 });
		target.draw( s );
	}
	

};

int main()
{

	O* o = new O();
	o->setOrigin(32,32);


	pe::Sprite* sp = new pe::Sprite(); sp->loadTexture("res/icon.png");
	(*o).setSprite(sp);

	pe::Background* bg = new pe::Background();
	//bg->loadTexture("res/bg.jpg");bg->setRepeatd(true);
	
	pe::Scene* scene = new pe::Scene("scene1");
	scene->addObject(o);
	scene->sortObjectsZIndex();
	scene->setBackground(bg);
	//scene->setDebugMode(true);
	

	pe::Application app;
	app.addScene( scene );
	app.setCurrentScene("scene1");
	app.update();
	return 0;
}