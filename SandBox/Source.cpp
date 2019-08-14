// pre-compile this
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <glm.hpp>

#include "Pixel-Engine.h"


class O : public pe::Object{
	
	void init() override {
		pe::Area* area = new pe::Area();
		auto rect = new sf::RectangleShape( sf::Vector2f(100,100) );
		rect->setFillColor( sf::Color(50, 75, 100, 255) );
		area->setShape( rect );
		setArea( area );
	}

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

	void process(double dt) override {}
	void draw(sf::RenderWindow* window) {
		auto s = sf::RectangleShape(sf::Vector2f(100,100));
		s.setPosition(20,20);
		//s.setOrigin(10,10);

		auto pos = sf::Mouse::getPosition(*window);
		print( pos.x << " " << pos.y );

		//print( s.getPoint(2).x << " " << s.getPoint(2).y  );
		//s.setRotation(45);
		window->draw( *(getArea()->getShape()) );
	}

};

int main()
{

	O* o = new O();
	pe::Sprite* sp = new pe::Sprite(); sp->loadTexture("res/icon.png");
	o->setSprite(sp); o->setPosition(100, 100);

	pe::Background* bg = new pe::Background();
	//bg->loadTexture("res/bg.jpg");bg->setRepeatd(true);
	
	pe::Scene* scene = new pe::Scene("scene1");
	scene->addObject(o);
	scene->sortObjectsZIndex();
	scene->setBackground(bg);
	

	pe::Application app;
	app.addScene( scene );
	app.setCurrentScene("scene1");
	app.update();
	return 0;
}