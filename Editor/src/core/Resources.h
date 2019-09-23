#pragma once

#include "pch.h"

class Resources
{
public:
	struct FileFormatIcons 
	{
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
		static sf::Texture FILE_HPP;
		static sf::Texture FILE_PNG;
		static sf::Texture FILE_TTF;
		static sf::Texture FILE_BIN;
		static sf::Texture FILE_DLL;
		static sf::Texture FILE_OBJ;
	};

	struct MenuIcons
	{
		static sf::Texture NONE;
		static sf::Texture RENAME;
		static sf::Texture _DELETE; // DELETE is a macro
		static sf::Texture OPEN_IN_EXPLORER;
	};

	struct OtherIcons 
	{
		static sf::Texture WARNING;
	};

	struct Fonts
	{
		static ImFont* PROGRAMMING;
	};


private:
	Resources() {}

	
};