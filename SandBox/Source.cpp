// pre-compile this or move them to pixel-engine.h
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <glm.hpp>

#include "Pixel-Engine.h"

#include "src/Player.h"
#include "src/Npc.h"



int main()
{
	
	REGISTER_CLASS( Player );
	REGISTER_CLASS( Npc );	

	pe::Application app;

	
	pe::AssetsReader r("test2.xml");
	r.readAssets(&app);
	
	
	app.setDebugMode(true);
	
	app.setCurrentScene( "scene1" );

	app.update();
	
	return 0;
}
