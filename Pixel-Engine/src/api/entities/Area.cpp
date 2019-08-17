#include "pch.h"
#include "Area.h"

namespace pe
{
	Area::~Area() {
		delete m_shape;
	}

	// getters
	bool Area::isContains(int x, int y) {
		return false; // TODO:
	}


	// getters
	std::size_t Area::getPointCount() const {
		assert( m_shape != nullptr );
		return m_shape->getPointCount();
	}
	sf::Vector2f Area::getPoint(std::size_t index) const {
		assert( m_shape != nullptr );
		return m_shape->getPoint(index);
	}

	// setters
	void Area::setPosition(float x, float y) {
		sf::Shape::setPosition(x, y);
		if (m_shape) m_shape->setPosition(getPosition());
	}
	void Area::setRotation(float angle) {
		sf::Shape::setRotation(angle);
		if (m_shape) m_shape->setRotation(getRotation());
	}
	void Area::setScale(float x, float y) {
		sf::Shape::setScale(x, y);
		if (m_shape) m_shape->setScale(getScale());
	}
	void Area::move(float x, float y) {
		setPosition(getPosition() + sf::Vector2f(x, y));
	}
	void Area::rotate(float angle) {
		setRotation(getRotation() + angle);
	}
	void Area::scale(float x, float y) {
		setScale(getScale().x * x, getScale().y * y);
	}

	void Area::setShape(sf::Shape* shape) {
		m_shape = shape;
		m_shape->setPosition(getPosition());
		m_shape->setRotation(getRotation());
		m_shape->setScale(getScale());
		m_shape->setFillColor(m_fill_color);
	}




}