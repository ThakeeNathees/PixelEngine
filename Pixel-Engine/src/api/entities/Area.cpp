#include "pch.h"
#include "Area.h"

namespace pe
{
	Area::~Area() {
		delete m_shape;
	}
	// getters
	bool Area::contains(glm::fvec2 point) {

		return false; // TODO: calculate scale rotation position ... 
	}

	// setters
	void Area::setShape(sf::RectangleShape* shape) {
		m_shape = shape;
		m_shape_type = ShapeType::RECTANGLE;
	}
	void Area::setShape(sf::CircleShape* shape) {
		m_shape = shape;
		m_shape_type = ShapeType::CIRCLE;
	}
	void Area::setShape(sf::ConvexShape* shape) {
		m_shape = shape;
		m_shape_type = ShapeType::CONVEX_POLYGON;
	}




}