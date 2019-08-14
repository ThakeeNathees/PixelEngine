#include "pch.h"
#include "Background.h"

namespace pe
{
	Background::Background() {}
	Background::~Background() {}

	void Background::loadTexture(std::string path) {
		m_texture.loadFromFile(path);
		m_background.setTexture(m_texture);
		setVisible(true);
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