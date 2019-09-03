// dependencies
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <glm.hpp>

// engine
#include "Pixel-Engine.h"

// classes for register
#include "src/Player.h"
#include "src/Npc.h"

void register_classes()
{
	REGISTER_CLASS(Player);
	REGISTER_CLASS(Npc);
}
