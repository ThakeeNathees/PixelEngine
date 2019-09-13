#pragma once
#include "../core.h"

#include "SFML/Graphics.hpp"
#include "Font.h"

namespace pe
{
	class Text : public sf::Text
	{
	public:
		Text() : sf::Text() {
			if (s_default_font) setFont(*s_default_font);
		}

		Text(const std::string& string, const Font& font, unsigned int characterSize = 30) 
			: sf::Text(string, font, characterSize) {}

		Text(const std::string& string, unsigned int characterSize = 30): sf::Text() {
			if (s_default_font) setFont(*s_default_font);
			setCharacterSize(characterSize);
			setString(string);
		}

		static void setDefaultFont(Font* font) {
			s_default_font = font;
		}
		static Font* getDefaultFont() {
			return s_default_font;
		}

	private:
		static pe::Font* s_default_font;
	};
}


