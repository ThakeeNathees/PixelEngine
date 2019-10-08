#include "pch.h"
#include "Area.h"

#include "..//utils/math_utils.h"

namespace pe
{
	int Area::s_area_count = 0;
	int Area::s_next_id = static_cast<int>(Asset::Type::Area);
	sf::Color Area::s_debug_shape_color = sf::Color(0, 0, 0, 255);
	float Area::s_outline_thickness = 2;

	Area::~Area() {
		s_area_count--;
	}

	// getters
	bool Area::isContains(float x, float y) {
		if (m_shape == nullptr) throw std::exception("Error: in pe::Area::isContains(float, float) -> m_shape was nullptr");
		return isContainPoint(*m_shape, sf::Vector2f(x, y));
	}

	// setters
	void Area::setPosition(float x, float y) {
		sf::Transformable::setPosition(x, y);
		if (m_shape) m_shape->setPosition(x, y);
	}
	void Area::setRotation(float angle) {
		sf::Transformable::setRotation(angle);
		if (m_shape) m_shape->setRotation(getRotation());
	}
	void Area::setScale(float x, float y) {
		sf::Transformable::setScale(x, y);
		if (m_shape) {
			m_shape->setScale(getScale());
			m_shape->setOutlineThickness( s_outline_thickness/std::max(x, y) );
		}
		
	}
	void Area::setOrigin(float x, float y) {
		sf::Transformable::setOrigin(x, y);
		if (m_shape) m_shape->setOrigin(x, y);
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
		if (!pe::isShapeConvex(*shape)) throw std::string("Error: in pe::Area::setShape(sf::Shape*) -> shape was concave, only convex supported");
		m_shape = shape;
		m_centroid = ::pe::getCentroid(shape);
		m_is_convex = isShapeConvex(*shape);
		m_shape->setPosition(getPosition());
		m_shape->setRotation(getRotation());
		m_shape->setScale(getScale());
		m_shape->setOutlineThickness(s_outline_thickness);
		m_shape->setOutlineColor(s_debug_shape_color);
		m_shape->setFillColor(sf::Color(0,0,0,0));
	}




}