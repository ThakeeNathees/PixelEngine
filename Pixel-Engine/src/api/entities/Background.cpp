#include "pch.h"
#include "Background.h"

namespace pe
{
	int Background::s_bg_count = 0;

	//void Background::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	//	if ( m_texture!= nullptr) target.draw( m_background );
	//}

	void Background::setTexture( Texture* texture) {
		m_texture = texture;
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
		//m_texture_rect_size = window_size;
		setTextureRect(sf::IntRect(offset.x, offset.y, window_size.x / getScale().x, window_size.y / getScale().y));
	}

	void Background::move(double dt) {
		if (m_move_speed.x && m_move_speed.y) return;
		auto rect = getTextureRect();
		setTextureRect( sf::IntRect( -(m_move_speed.x*dt) + rect.left, -(m_move_speed.y*dt) + rect.top,  rect.width, rect.height) );
	}


}