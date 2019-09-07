#pragma once
#include "../core.h"


#define PI 3.141592654

namespace pe
{

	
	inline sf::Vector2f rotatePoint(float x, float y, float angle_degree) {
		float angle = angle_degree * PI / 180.0f;
		sf::Vector2f rotated;
		rotated.x = x * glm::cos(angle) - y * glm::sin(angle);
		rotated.y = y * glm::cos(angle) + x * glm::sin(angle);
		return rotated;
	}

	inline sf::Vector2f rotatePoint(sf::Vector2f point, float angle_degree) { return rotatePoint(point.x, point.y, angle_degree); }

	inline float vectCross(const sf::Vector2f& vec2, const sf::Vector2f& vec1) { // return magnitude in z axis
		return  vec1.x * vec2.y - vec1.y * vec2.x;
	}

	
	inline sf::Vector2f getCentroid(sf::Shape * shape) {
		sf::Vector2f centroid;
		double signed_area = 0;
		for (int i = 0; i < shape->getPointCount() - 1; i++) {
			auto p0 = shape->getPoint(i);
			auto p1 = shape->getPoint((i + 1) % shape->getPointCount());
			signed_area += p0.x * p1.y - p1.x * p0.y;
		}
		signed_area *= .5;

		for (int i = 0; i < shape->getPointCount(); i++) {
			auto p0 = shape->getPoint(i);
			auto p1 = shape->getPoint((i + 1) % shape->getPointCount());
			centroid.x += (p0.x + p1.x) * (p0.x * p1.y - p1.x * p0.y);
			centroid.y += (p0.y + p1.y) * (p0.x * p1.y - p1.x * p0.y);
		}

		centroid.x /= (6 * signed_area);
		centroid.y /= (6 * signed_area);

		return centroid;

	}

	inline bool isShapeConvex(const sf::Shape& shape) {
		if (shape.getPointCount() <= 3) return true;

		for (int i = 0; i < shape.getPointCount(); i++) {

			sf::Vector2f point0 = shape.getPoint(i % shape.getPointCount());
			sf::Vector2f point1 = shape.getPoint((i + 1) % shape.getPointCount());
			sf::Vector2f point2 = shape.getPoint((i + 2) % shape.getPointCount());
			sf::Vector2f point3 = shape.getPoint((i + 3) % shape.getPointCount());

			float cross0 = vectCross(point2 - point1, point1 - point0);
			float cross1 = vectCross(point3 - point2, point2 - point1);

			if (cross0 * cross1 < 0) return false;
		}
		return true;
	}


	inline bool isContainPoint(const sf::Shape& shape, sf::Vector2f point) {
		if (shape.getPointCount() < 3) return false;

		for (int i = 0; i < shape.getPointCount(); i++) {

			sf::Vector2f point0 = shape.getTransform().transformPoint(shape.getPoint(i % shape.getPointCount()));
			sf::Vector2f point1 = shape.getTransform().transformPoint(shape.getPoint((i + 1) % shape.getPointCount()));
			sf::Vector2f point2 = shape.getTransform().transformPoint(shape.getPoint((i + 2) % shape.getPointCount()));

			float cross0 = vectCross(point - point1, point1 - point0);
			float cross1 = vectCross(point - point2, point2 - point1);

			if (cross0 * cross1 < 0) return false;
		}
		return true;
	}

	// return if any point of shape2 is inside shape1 ?
	inline bool isShape2InShape1(const sf::Shape& shape1, const sf::Shape& shape2) {
		for (int i = 0; i < shape2.getPointCount(); i++) {
			auto shape2_point = shape2.getTransform().transformPoint( shape2.getPoint(i) );
			if (isContainPoint(shape1, shape2_point)) {
				return true;
			}
		}
		return false;
	}
	inline bool isIntersecting(const sf::Shape& shape1, const sf::Shape& shape2) {
		bool shpae2_in_shape1 = isShape2InShape1(shape1, shape2);
		bool shpae1_in_shape2 = isShape2InShape1(shape2, shape1);
		return shpae2_in_shape1 || shpae1_in_shape2;
	}

	// TODO: interpolate vector template function

}