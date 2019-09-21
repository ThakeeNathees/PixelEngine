#pragma once

#include "pch.h"

class Resources
{
public:
	struct Icons {
		static sf::Texture DIR_CLOSED;
		static sf::Texture DIR_OPEN;
		static sf::Texture FILE_TEXT;
		static sf::Texture FILE_PY;
		static sf::Texture FILE_CPP;
		static sf::Texture FILE_H;
		static sf::Texture FILE_PNG;
		static sf::Texture FILE_TTF;
		static sf::Texture FILE_BIN;
	};

	static void init();

private:
	Resources() {}

	
};