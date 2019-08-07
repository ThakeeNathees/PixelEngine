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

	void Sprite::setFrameIndex(int index) {
		/* TODO:
		      check if rect applied on texture or sprite (rotated and tranformed)
			  and apply rect with index, and m_frames
		*/
		   
	}

	
	
}