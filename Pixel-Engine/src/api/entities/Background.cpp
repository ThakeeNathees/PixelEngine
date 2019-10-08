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

	void Background::setRepeated(bool repeated) {
		if (m_texture == nullptr) throw std::exception("Error: in pe::Background::setRepeated(bool) -> texture was nullptr");
		m_texture->setRepeated(repeated);
	}

	void Background::setSmooth(bool smooth) {
		if (m_texture == nullptr) throw std::exception("Error: in pe::Background::setSmooth(bool) -> texture was nullptr");
		m_texture->setSmooth(smooth);
	}

	void Background::setTextureRectSize(sf::Vector2i size, sf::Vector2i offset) {
		if (!m_texture->isRepeated()) return;
		setTextureRect(sf::IntRect(offset.x, offset.y, size.x / getScale().x, size.y / getScale().y));
	}

	void Background::move(double dt) {
		if (!m_move_speed.x && !m_move_speed.y) return;
		if (! m_texture->isRepeated()) throw std::exception("Error: in pe::Background::move(double) -> texture must be repeated");
		auto rect = getTextureRect();
		setTextureRect( sf::IntRect( -(m_move_speed.x*dt) + rect.left, -(m_move_speed.y*dt) + rect.top,  rect.width, rect.height) );
	}


}