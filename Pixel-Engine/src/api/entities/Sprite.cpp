#include "pch.h"
#include "Sprite.h"

namespace pe
{

	int Sprite::s_sprite_count = 0;
	int Sprite::s_next_id = static_cast<int>( Asset::Type::Sprite );

	// setters
	void Sprite::setTexture( Texture& texture, bool resetRect) {
		m_texture = &texture;
		sf::Sprite::setTexture( texture, resetRect );
	}

	void Sprite::setFrameIndex(int index) {
		m_frame_index = index;

		if ((index < 0) || (index > getFrameCount())) {
			throw std::exception("Error: in pe::Sprite::setFrameIndex(int) -> invalid frame index");
		}
		if (!m_texture) {
			throw std::exception("Error: in pe::Sprite::setFrameIndex(ind) -> texture was nullptr, assign a texture first");
		}
		int width  = m_texture->getSize().x / std::get<0>(m_frames).x;
		int height = m_texture->getSize().y / std::get<0>(m_frames).y;
		int left = (index % (std::get<0>(m_frames).x))* width;
		int top  = (index / (std::get<0>(m_frames).x))* height;
		sf::IntRect rect( left + std::get<1>(m_frames).x, top + std::get<1>(m_frames).y, width, height );
		setTextureRect(rect); 
	}

	// getters
	void Sprite::setFrames(int x, int y, int offset_x, int offset_y) {
		if (x < 0 || y < 0) throw std::exception("Error: in pe::Sprite::SetFrames(int, int [, int, int]) -> x<0 or y<0");
		std::get<0>(m_frames).x = x; std::get<0>(m_frames).y = y; std::get<1>(m_frames).x = offset_x; std::get<1>(m_frames).y = offset_y;
		setFrameIndex(0);
	}

	void Sprite::setFrames(const std::tuple<sf::Vector2i, sf::Vector2i>& frames) {
		setFrames(std::get<0>(frames).x, std::get<0>(frames).y, std::get<1>(frames).x, std::get<1>(frames).y);
	}


}