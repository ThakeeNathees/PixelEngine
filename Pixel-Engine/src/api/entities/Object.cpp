#include "pch.h"
//#include "Object.h"
#include "..//Scene.h" // for referencing m_scene

namespace pe
{

	int Object::s_object_count = 0;

	Object::Object() {
		m_id = ++s_object_count;
	}
	Object::~Object() {
		delete m_sprite;
	}
	// TODO: move applyTransform this one and the one inside the area to util
	void Object::applyTransform(sf::Transformable* to, sf::Transformable* from) {
		if (to && from) {
			to->setPosition( from->getPosition() );
			to->setRotation( from->getRotation() );
			to->setScale( from->getScale() );
		}
	}

	// virtual function
	void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		draw(target);
		drawDebug(target);
	}
	void Object::draw(sf::RenderTarget& target) const {
		target.draw(*getSprite());
	}
	void Object::drawDebug(sf::RenderTarget& target) const {
		if (m_scene != nullptr && m_scene->isDebugMode() ) {
			if (m_area != nullptr) target.draw(*(m_area->getShape()));
		}
	}

	// setters
	void Object::setPosition(float x, float y) {
		sf::Transformable::setPosition(x, y);
		if (m_sprite) m_sprite->setPosition( getPosition() );
		if (m_area) m_area->setPosition( getPosition() );
	}
	void Object::setRotation(float angle) {
		sf::Transformable::setRotation(angle);
		if (m_sprite) m_sprite->setRotation( getRotation() );
		if (m_area) m_area->setRotation( getRotation() );
	}
	void Object::setScale(float x, float y) {
		sf::Transformable::setScale(x, y);
		if (m_sprite) m_sprite->setScale(getScale());
		if (m_area) m_area->setScale(getScale());
	}

	void Object::setZIndex(int z_index) {
		m_z_index = z_index;
		// TODO: signal call Scene.sortObjectZIndex() 
	}
	void Object::setSprite(Sprite* sprite) {
		m_sprite = sprite;
		applyTransform(m_sprite, this);
	}
	void Object::setArea(Area* area) {
		m_area = area;
		applyTransform(m_area, this);
	}

}