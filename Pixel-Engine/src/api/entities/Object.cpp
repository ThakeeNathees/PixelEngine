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


	// virtual function
	void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		states.transform *= getTransform(); // apply transform to member drawables
		target.draw(*getSprite(), states);
		if (m_scene != nullptr ) {
			//if (m_area != nullptr) target.draw(*(m_area->getShape()), states);
		}
	}

	// setters
	void Object::setSprite(Sprite* sprite) {
		m_sprite = sprite;
	}
	void Object::setZIndex(int z_index) {
		m_z_index = z_index;
		// TODO: signal call Scene.sortObjectZIndex() 
	}
	void Object::setArea(Area* area) {
		m_area = area;
	}

}