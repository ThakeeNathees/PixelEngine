#include "pch.h"
#include "Object.h"

namespace pe
{

	int Object::s_object_count = 0;

	Object::Object() {
		m_id = ++s_object_count;
	}
	Object::~Object() {
		delete m_sprite;
	}


	// setters
	void Object::setPosition(glm::vec2 position) {
		m_position = position;
		m_sprite->setPosition(position.x, position.y);
	}
	void Object::setPosition(float x, float y) {
		setPosition(glm::vec2(x, y));
	}
	void Object::setSprite(Sprite* sprite) {
		m_sprite = sprite;
		m_sprite->setPosition(m_position.x, m_position.y);
	}

	void Object::setZIndex(int z_index) {
		m_z_index = z_index;
		// TODO: signal call Scene.sortObjectZIndex() 
	}

}