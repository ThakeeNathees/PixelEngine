#include "pch.h"
#include "Area.h"

namespace pe
{
	Area::~Area() {
		delete m_shape;
	}

	void Area::applyTransform(sf::Transformable* to, sf::Transformable* from) {
		if (to && from) {
			to->setPosition(from->getPosition());
			to->setRotation(from->getRotation());
			to->setScale(from->getScale());
		}
	}

	// getters
	bool Area::contains(glm::fvec2 point) {

		return false; // TODO: calculate scale rotation position ... 
	}

	// setters
	void Area::setPosition(float x, float y) {
		sf::Transformable::setPosition(x, y);
		if (m_shape) m_shape->setPosition(getPosition());
	}
	void Area::setRotation(float angle) {
		sf::Transformable::setRotation(angle);
		if (m_shape) m_shape->setRotation(getRotation());
	}
	void Area::setScale(float x, float y) {
		sf::Transformable::setScale(x, y);
		if (m_shape) m_shape->setScale(getScale());
	}


	void Area::setShape(sf::RectangleShape* shape) {
		m_shape = shape;
		applyTransform(m_shape, this);
		m_shape_type = ShapeType::RECTANGLE;
	}
	void Area::setShape(sf::CircleShape* shape) {
		m_shape = shape;
		applyTransform(m_shape, this);
		m_shape_type = ShapeType::CIRCLE;
	}
	void Area::setShape(sf::ConvexShape* shape) {
		m_shape = shape;
		applyTransform(m_shape, this);
		m_shape_type = ShapeType::CONVEX_POLYGON;
	}




}