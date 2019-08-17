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

	void Object::move(float x, float y) {
		setPosition( getPosition() + sf::Vector2f(x, y) );
	}
	void Object::rotate(float angle) {
		setRotation( getRotation() + angle );
	}
	void Object::scale(float x, float y) {
		setScale(  getScale().x * x, getScale().y * y  );
	}

	void Object::setZIndex(int z_index) {
		m_z_index = z_index;
		// TODO: signal call Scene.sortObjectZIndex() 
	}
	void Object::setSprite(Sprite* sprite) {
		m_sprite = sprite;
		m_sprite->setPosition(getPosition());
		m_sprite->setRotation(getRotation());
		m_sprite->setScale(getScale());
	}
	void Object::setArea(Area* area) { // if area == nullptr -> area set as sprite rect.
		if (area == nullptr && m_sprite != nullptr ) {
			if (m_area) delete m_area;
			auto rect = m_sprite->getLocalBounds();
			sf::RectangleShape* shape = new sf::RectangleShape( sf::Vector2f(rect.width, rect.height) );
			auto area = new Area();
			area->setShape( shape );
			setArea( area );
		}
		else {
			m_area = area;
			m_area->setPosition(getPosition());
			m_area->setRotation(getRotation());
			m_area->setScale(getScale());
		}
	}

}