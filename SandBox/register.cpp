
// engine
#define PE_PROJECT SandBox
#include "Pixel-Engine.h"


// classes for register
#include "src/Player.h"
#include "src/Npc.h"

void register_classes()
{
	// register cpp objects
	REGISTER_CLASS(Player);
	REGISTER_CLASS(Npc);

	// add python object path
	ADD_PYOBJECT_PATH("src");
}
