// pre-compile this or move them to pixel-engine.h
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <glm.hpp>

#include "Pixel-Engine.h"

#include "src/Player.h"
#include "src/Npc.h"



int main()
{
	pe::Scene* scene = new pe::Scene("scene1");
	pe::XmlFile f;
	// add objects
	pe::Object* player = new Player;
	player->setName("Player");
	scene->addObject( player );

	pe::Object* npc = new Npc;
	npc->setName("Npc");
	scene->addObject( npc );
	
	
	scene->sortObjectsZIndex();
	
	pe::Application app;
	//app.setDebugMode(true);

	app.addScene( scene );
	app.setCurrentScene("scene1");
	app.update();
	return 0;
}
