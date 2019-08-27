#include "pch.h"
#include "Sprite.h"

namespace pe
{

	int Sprite::s_sprite_count = 0;

	// setters
	void Sprite::setTexture( Texture* texture, bool resetRect) {
		m_texture = texture;
		sf::Sprite::setTexture( *texture, resetRect );
	}

	void Sprite::setFrameIndex(int index) {
		m_frame_index = index;
		assert( (index >=0) &&  (index < getFrameCount()) && "invalid sprite frame index" );
		assert( hasTexture() && "cant set frames without any textures" );
		int width  = getTexture().getSize().x / m_frames.x;
		int height = getTexture().getSize().y / m_frames.y;
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

	void Sprite::setFrames(const glm::ivec4& frames) {
		setFrames(frames.x, frames.y, frames.z, frames.w);
	}

	
	
}