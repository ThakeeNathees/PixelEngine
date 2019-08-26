#include "pch.h"
#include "Background.h"

namespace pe
{
	int Background::s_bg_count = 0;

	void Background::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		if ( m_texture!= nullptr) target.draw( m_background );
	}

	void Background::setTexture( Texture* texture) {
		m_texture = texture;
		m_background.setTexture(*m_texture);
	}

	void Background::setRepeatd(bool repeated) {
		m_texture->setRepeated(repeated);
		if (m_texture_rect_size.x > 0 && m_texture_rect_size.y > 0) {
			m_background.setTextureRect(sf::IntRect(0, 0, m_texture_rect_size.x, m_texture_rect_size.y));
		}
	}

	void Background::setTextureRectSize(glm::ivec2 window_size, glm::ivec2 offset) {
		m_texture_rect_size = window_size;
		m_background.setTextureRect(sf::IntRect(offset.x, offset.y, m_texture_rect_size.x / m_background.getScale().x, m_texture_rect_size.y / m_background.getScale().y));	
	}

	void Background::move(glm::ivec2 vec) {
		auto rect = m_background.getTextureRect();
		m_background.setTextureRect( sf::IntRect( -vec.x + rect.left, -vec.y + rect.top,  rect.width, rect.height) );
	}


}