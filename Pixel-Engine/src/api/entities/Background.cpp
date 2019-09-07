#include "pch.h"
#include "Background.h"

namespace pe
{
	int Background::s_bg_count = 0;
	int Background::s_next_id = static_cast<int>(Asset::Type::Background);


	void Background::setTexture( Texture& texture) {
		m_texture = &texture;
		sf::Sprite::setTexture(*m_texture,true);
	}

	void Background::setRepeatd(bool repeated) {
		assert( m_texture );
		m_texture->setRepeated(repeated);
	}

	void Background::setSmooth(bool smooth) {
		assert( m_texture );
		m_texture->setSmooth(smooth);
	}

	void Background::setTextureRectSize(sf::Vector2i size, sf::Vector2i offset) {
		if (!m_texture->isRepeated()) return;
		setTextureRect(sf::IntRect(offset.x, offset.y, size.x / getScale().x, size.y / getScale().y));
	}

	void Background::move(double dt) {
		if (!m_move_speed.x && !m_move_speed.y) return;
		assert(m_texture->isRepeated());
		auto rect = getTextureRect();
		setTextureRect( sf::IntRect( -(m_move_speed.x*dt) + rect.left, -(m_move_speed.y*dt) + rect.top,  rect.width, rect.height) );
	}


}