// pre-compile this
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <glm.hpp>

#include "Pixel-Engine.h"


class O : public pe::Object{};

int main()
{

	pe::Object* o = new pe::Object();
	pe::Sprite* sp = new pe::Sprite(); sp->loadTexture("res/icon.png");
	o->setSprite(sp); o->setPosition(100, 100);

	O* oo = new O();
	pe::Sprite* ss = new pe::Sprite(); ss->loadTexture("res/sheet.png");
	oo->setSprite(ss); oo->setPosition(200,200);
	
	pe::Scene* scene = new pe::Scene();
	scene->addObject(o);
	scene->addObject(oo);

	pe::Application app;
	app.addScene( "scene1", scene);
	app.setCurrentScene("scene1");
	app.update();
	return 0;
}