#pragma once

#include "Pixel-Engine.h"

class RenderWindow
{
public:
	static void init();
	static void renderRenderWindow();
	inline static glm::vec2 getMousePos() { return s_mouse_pos; }

	static void listenEvent(sf::Event& event);


	//TEST
	static pe::Sprite* test_sprite;
private:
	static sf::RenderTexture* s_render_texture;
	static glm::vec2 s_mouse_pos;
};