#pragma once

#include "..//core.h"


namespace pe {

	class Sprite : public sf::Sprite
	{
	public:
		bool loadTexture(const char* path);
		//void setTexture(const sf::Texture& texture); in sfml

	private:
		sf::Texture m_texture;
		bool visible = true;
	};

}

