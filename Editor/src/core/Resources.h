#pragma once

#include "pch.h"

class Resources
{
public:
	struct Icons {
		static sf::Texture DIR_CLOSED;
		static sf::Texture DIR_OPEN;
		static sf::Texture _FILE_UNKNOWN; // FILE_UNKNOWN is a macro
		static sf::Texture FILE_PEPROJ;
		static sf::Texture FILE_TEXT;
		static sf::Texture FILE_XML;
		static sf::Texture FILE_PY;
		static sf::Texture FILE_PYC;
		static sf::Texture FILE_CPP;
		static sf::Texture FILE_H;
		static sf::Texture FILE_PNG;
		static sf::Texture FILE_TTF;
		static sf::Texture FILE_BIN;
		static sf::Texture FILE_DLL;
		static sf::Texture FILE_OBJ;
	};


private:
	Resources() {}

	
};