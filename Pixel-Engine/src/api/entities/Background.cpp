#include "pch.h"
#include "Background.h"

namespace pe
{
	int Background::s_bg_count = 0;

	void Background::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		if ( m_has_image && m_visible) target.draw( m_background );
	}

	bool Background::loadTexture(std::string path) {
		bool success = m_texture.loadFromFile(path);
		if (!success) return false;
		m_background.setTexture(m_texture);
		m_has_image = true;
		return true;
	}

	void Background::setRepeatd(bool repeated) {
		m_texture.setRepeated(repeated);
		if (m_window_size.x > 0 && m_window_size.y > 0) {
			m_background.setTextureRect(sf::IntRect(0, 0, m_window_size.x, m_window_size.y));
		}
	}

	void Background::setBgWindowSize(glm::ivec2 window_size) { 
		m_window_size = window_size;
		m_background.setTextureRect(sf::IntRect(0, 0, m_window_size.x, m_window_size.y));
	}


}