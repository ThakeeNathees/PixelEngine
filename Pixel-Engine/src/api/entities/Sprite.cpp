#include "pch.h"
#include "Sprite.h"

namespace pe
{

	int Sprite::s_sprite_count = 0;

	Sprite::Sprite() : m_frame_index(0) {
		m_id = ++s_sprite_count;
	}

	// setters
	bool Sprite::loadTexture(const std::string& path, bool reset_rect)
	{
		bool success = m_texture.loadFromFile(path.c_str());
		setTexture(m_texture, reset_rect);
		return success;
	}

	void Sprite::setFrameIndex(int index) {
		assert( (index >=0) &&  (index < getFrameCount()) && "invalid sprite frame index" );
		int width  = getTexture()->getSize().x / m_frames.x;
		int height = getTexture()->getSize().y / m_frames.y;
		int left = (index % (m_frames.x))* width;
		int top  = (index / (m_frames.x))* height;

		sf::IntRect rect( left + m_frames.z, top + m_frames.w, width, height );
		setTextureRect(rect); 
	}

	// getters
	void Sprite::setFrames(int x, int y, int offset_x, int offset_y) {
		assert(x > 0 && y > 0);
		m_frames.x = x; m_frames.y = y; m_frames.z = offset_x; m_frames.w = offset_y;
		setFrameIndex(m_frame_index);
	}

	
	
}