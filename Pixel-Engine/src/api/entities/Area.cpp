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
	bool Area::isContains(int x, int y) {

		switch (m_shape_type) {
		case ShapeType::RECTANGLE:
		{ // TODO: apply rotation
			sf::Vector2f p1; // point top left
			sf::Vector2f p2; // point bottom right
			p1.x = m_shape->getPoint(0).x * m_shape->getScale().x;
			p1.y = m_shape->getPoint(0).y * m_shape->getScale().y;

			p1 = rotatePoint<sf::Vector2f>(p1, m_shape->getRotation());
			p2 = rotatePoint<sf::Vector2f>(p2, m_shape->getRotation());

			p2.x = m_shape->getPoint(2).x * m_shape->getScale().x;
			p2.y = m_shape->getPoint(2).y * m_shape->getScale().y;

			p1 += m_shape->getPosition() - m_shape->getOrigin();
			p2 += m_shape->getPosition() - m_shape->getOrigin();
			return p1.x <= x && x <= p2.x &&
				p1.y <= y && y <= p2.y;
		}
		default:
			return false; // TODO: calculate scale rotation position ... 
		}

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