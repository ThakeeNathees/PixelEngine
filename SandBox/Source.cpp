// pre-compile this or move them to pixel-engine.h
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <glm.hpp>

#include "Pixel-Engine.h"


class O : public pe::Object{
	
	void init() override {
	}

	bool input(sf::Event& event) override {
		if (event.type == sf::Event::EventType::KeyPressed) {
			if (event.key.code == 0) {
				rotate(1);
				return true;
			};
			if (event.key.code == 3) {
				//move(10,0);
			};
		}
		return false;
	}

	void process(double dt) override {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
			//move( 100 * dt, 0 );
		}
		auto app = getApplication();
		auto pos = sf::Mouse::getPosition( *app->getWindow() );
		
		//print(  ( (getArea()->isContains(pos) )?"inside":"outside" )  );
	}

	void draw(sf::RenderTarget& target) const override {
		sf::CircleShape s(100);

		s.setPosition(200,200);
		
		auto pos = sf::Mouse::getPosition(*getApplication()->getWindow());
		print( pe::isContainPoint( s, {pos.x, pos.y}  ) );
		target.draw( s );
	}

};

int main()
{

	O* o = new O();
	o->setOrigin(32, 32);
	o->setPosition(100,100);
	//o->setScale( .5,.5 );

	pe::Sprite* sp = new pe::Sprite(); sp->loadTexture("res/icon.png");
	(*o).setSprite(sp);

	pe::Area* area = new pe::Area();
	auto rect = new sf::RectangleShape(sf::Vector2f(64, 64));
	rect->setFillColor(sf::Color(255, 10, 100, 200));
	area->setShape(rect);
	o->setArea(area);

	o->rotate( 45 );


	pe::Background* bg = new pe::Background();
	//bg->loadTexture("res/bg.jpg");bg->setRepeatd(true);
	
	pe::Scene* scene = new pe::Scene("scene1");
	scene->addObject(o);
	scene->sortObjectsZIndex();
	scene->setBackground(bg);
	scene->setDebugMode(true);
	

	pe::Application app;
	app.addScene( scene );
	app.setCurrentScene("scene1");
	app.update();
	return 0;
}