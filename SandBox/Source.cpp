// pre-compile this or move them to pixel-engine.h
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <glm.hpp>

#include "Pixel-Engine.h"

#include "src/Player.h"
#include "src/Npc.h"




int main()
{
	pe::Background* bg = new pe::Background();
	pe::Texture* tex = new pe::Texture();
	tex->loadFromFile("res/logo.png");
	bg->setTexture(tex);
	bg->getBgSprite().setScale(.15,.15);
	bg->setRepeatd(true);

	pe::Scene* scene = new pe::Scene("scene1");
	//scene->setBackground(bg);
	// add objects
	pe::Object* player = new Player;
	player->setName("Player");
	scene->addObject( player );

	pe::Object* npc = new Npc;
	npc->setName("Npc");
	scene->addObject( npc );
	scene->sortObjectsZIndex();
	
	pe::Application app;
	app.setDebugMode(true);
	app.addScene( scene );
	app.setCurrentScene(scene->getName());
	app.update();
	return 0;
}
