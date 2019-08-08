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
		int width  = getTexture()->getSize().x / m_frames.x;
		int height = getTexture()->getSize().y / m_frames.y;
		int left = (index % (m_frames.x))* width;
		int top  = (index / (m_frames.y))* height;

		sf::IntRect rect( left + m_frames.z, top + m_frames.w, width, height );
		setTextureRect(rect);
		/* TODO:
		      check if rect applied on texture or sprite (rotated and tranformed)
			  and apply rect with index, and m_frames
		*/
		   
	}

	
	
}