#pragma once

#include "Pixel-Engine.h"

class RenderWindow
{
public:
	static void init();
	static void renderRenderWindow();
	//TEST
	static pe::Sprite* test_sprite;
private:
	static sf::RenderTexture* render_texture;
};