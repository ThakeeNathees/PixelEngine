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
	REGISTER_CLASS( Player );
	REGISTER_CLASS( Npc );

	

	pe::Application app;

	pe::Background* bg = pe::Assets::newAsset<pe::Background>();
	pe::Texture* tex = pe::Assets::newAsset<pe::Texture>();

	tex->loadFromFile("res/logo.png");
	bg->setTexture(*tex);
	bg->setScale(.15,.15);
	bg->setRepeatd(true);

	pe::Scene* scene = new pe::Scene("scene1");

	pe::Object* player = pe::Assets::constructObj("Player");
	player->setName("player1");
	scene->addObject( player );

	pe::Object* npc = pe::Assets::constructObj("Npc");
	npc->setName("Npc");
	scene->addObject( npc );
	scene->sortZIndex();

	
	
	app.setDebugMode(true);
	app.addScene( scene );
	app.setCurrentScene(scene->getName());

	app.update();
	return 0;
}
