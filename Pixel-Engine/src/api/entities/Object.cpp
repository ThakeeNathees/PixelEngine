#include "pch.h"
#include "Object.h"

namespace pe
{
	void Object::setPosition(glm::vec2 position) {
		m_position = position;
		m_sprite.setPosition(position.x, position.y);
	}
	void Object::setPosition(float x, float y) {
		setPosition(glm::vec2(x, y));
	}
	void Object::setSprite(Sprite sprite) {
		m_sprite = sprite;
		m_sprite.setPosition(m_position.x, m_position.y);
	}
}