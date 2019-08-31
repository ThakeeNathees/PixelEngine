#include "pch.h"
#include "Background.h"

namespace pe
{
	int Background::s_bg_count = 0;
	int Background::s_next_id = static_cast<int>(Asset::Type::Background);


	void Background::setTexture( Texture& texture) {
		m_texture = &texture;
		sf::Sprite::setTexture(*m_texture);
	}

	void Background::setRepeatd(bool repeated) {
		assert( hasTexture() );
		m_repeated = repeated;
		m_texture->setRepeated(repeated);
	}

	void Background::setSmooth(bool smooth) {
		assert( hasTexture() );
		m_smooth = smooth;
		m_texture->setSmooth(smooth);
	}

	void Background::setTextureRectSize(glm::ivec2 window_size, glm::ivec2 offset) {
		setTextureRect(sf::IntRect(offset.x, offset.y, window_size.x / getScale().x, window_size.y / getScale().y));
	}

	void Background::move(double dt) {
		if (m_move_speed.x && m_move_speed.y) return;
		auto rect = getTextureRect();
		setTextureRect( sf::IntRect( -(m_move_speed.x*dt) + rect.left, -(m_move_speed.y*dt) + rect.top,  rect.width, rect.height) );
	}


}