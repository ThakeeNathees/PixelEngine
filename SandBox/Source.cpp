// pre-compile this or move them to pixel-engine.h
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <glm.hpp>

#include "Pixel-Engine.h"

#include "src/Player.h"
#include "src/Npc.h"

class o : public pe::Object
{
public:
};


int main()
{
	REGISTER_CLASS( o );
	pe::Object* obj = pe::Assets::constructObj("o");

	print( obj->getName() );

	pe::Application app;

	pe::Background* bg = pe::Assets::newAsset<pe::Background>();
	pe::Texture* tex = pe::Assets::newAsset<pe::Texture>();

	tex->loadFromFile("res/logo.png");
	bg->setTexture(*tex);
	bg->setScale(.15,.15);
	bg->setRepeatd(true);

	pe::Scene* scene = new pe::Scene("scene1");

	pe::Object* player = new Player;
	player->setName("Player");
	scene->addObject( player );

	pe::Object* npc = new Npc;
	npc->setName("Npc");
	scene->addObject( npc );
	scene->sortZIndex();
	
	app.setDebugMode(true);
	app.addScene( scene );
	app.setCurrentScene(scene->getName());

	app.update();
	return 0;
}
