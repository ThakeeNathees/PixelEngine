#pragma once

#include "..//globals.h"


class ImageViwer
{

public:
	static void renderImageViwer();
	static void setImage(const char* path);
	inline static void setPOpen(bool val) { s_p_open = val; }

private:
	static sf::Texture s_texture;
	static bool s_p_open;
};