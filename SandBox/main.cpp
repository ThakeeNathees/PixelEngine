#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <glm.hpp>

#include "Pixel-Engine.h"

#include "src/Player.h"
#include "src/Npc.h"

void register_classes()
{
	REGISTER_CLASS(Player);
	REGISTER_CLASS(Npc);
}
