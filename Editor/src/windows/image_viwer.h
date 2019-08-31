#pragma once

#include "..//globals.h"


#include "Pixel-Engine.h"

class ImageViwer
{
	ImageViwer() = delete;
public:
	static void init();
	static void renderImageViwer();
	static void setImage(const char* path);
	static void listenEvent(sf::Event& event);
	inline static void setPOpen(bool val) { s_p_open = val; }

private:
	static bool s_p_open;
	static sf::Texture s_texture;
	static sf::Sprite s_sprite;
	static sf::RenderTexture s_render_texture;

	static bool s_texture_smooth;

	static sf::Vector2f s_mouse_middle_pos; // for image move with middle mouse button
	static sf::Vector2f s_sprite_init_pos; // for image move with middle mouse button
};