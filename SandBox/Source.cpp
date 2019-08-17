// pre-compile this or move them to pixel-engine.h
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <glm.hpp>

#include "Pixel-Engine.h"

#include "src/Object1.h"

int main()
{



	pe::Scene* scene = new pe::Scene("scene1");
	Object1* obj = new Object1();

	// add objects
	scene->addObject( obj );
	
	//scene->setBackground(bg);
	scene->sortObjectsZIndex();
	scene->setDebugMode(true);
	
	pe::Application app;
	app.addScene( scene );
	app.setCurrentScene("scene1");
	app.update();
	return 0;
}