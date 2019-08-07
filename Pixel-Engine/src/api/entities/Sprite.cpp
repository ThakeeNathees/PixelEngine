#include "pch.h"
#include "Sprite.h"

namespace pe
{
	bool Sprite::loadTexture(const char* path)
	{
		bool success = m_texture.loadFromFile(path);
		setTexture(m_texture);
		return success;
	}

	
}