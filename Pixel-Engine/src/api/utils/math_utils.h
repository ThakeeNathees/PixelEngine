#pragma once
#include "../core.h"


#define PI 3.141592654

namespace pe
{
	template<typename T1 = glm::fvec2, typename T2 = sf::Vector2f>
	T1 convertVect(const T2 & vect) {
		T1 _vect;
		_vect.x = vect.x;
		_vect.y = vect.y;
		return _vect;
	}

	template<typename T = glm::fvec2>
	T rotatePoint(float x, float y, float angle_degree) {
		float angle = angle_degree * PI / 180.0f;
		T rotated;
		rotated.x = x * glm::cos(angle) - y * glm::sin(angle);
		rotated.y = y * glm::cos(angle) + x * glm::sin(angle);
		return rotated;
	}
	template<typename T = glm::fvec2>
	T rotatePoint(glm::fvec2 point, float angle_degree) { return rotatePoint<T>(point.x, point.y, angle_degree); }
	template<typename T = glm::fvec2>
	T rotatePoint(sf::Vector2f point, float angle_degree) { return rotatePoint<T>(point.x, point.y, angle_degree); }

	inline float vectCross(const glm::fvec2& vec2, const glm::fvec2& vec1) { // return magnitude in z axis
		return  vec1.x * vec2.y - vec1.y * vec2.x;
	}

	template <typename T = sf::Vector2f>
	T getCentroid(sf::Shape * shape) {
		T centroid;
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

	template <typename T1 = glm::fvec2, typename T2 = sf::Vector2f>
	T1 applyTransform(T2 point, const sf::Transformable & shape) {
		sf::Vector2f transformed = shape.getTransform().transformPoint(sf::Vector2f(point.x, point.y));
		return T1(transformed.x, transformed.y);
		/* similer code of mine
		point -= shape.getOrigin();
		point.x *= shape.getScale().x;
		point.y *= shape.getScale().y;
		point = rotatePoint<sf::Vector2f>(point, shape.getRotation());
		point += shape.getPosition();
		return T1(point.x, point.y);
		*/
	}

	inline bool isShapeConvex(const sf::Shape& shape) {
		if (shape.getPointCount() <= 3) return true;

		for (int i = 0; i < shape.getPointCount(); i++) {

			glm::fvec2 point0 = convertVect(shape.getPoint(i % shape.getPointCount()));
			glm::fvec2 point1 = convertVect(shape.getPoint((i + 1) % shape.getPointCount()));
			glm::fvec2 point2 = convertVect(shape.getPoint((i + 2) % shape.getPointCount()));
			glm::fvec2 point3 = convertVect(shape.getPoint((i + 3) % shape.getPointCount()));

			float cross0 = vectCross(point2 - point1, point1 - point0);
			float cross1 = vectCross(point3 - point2, point2 - point1);

			if (cross0 * cross1 < 0) return false;
		}
		return true;
	}


	inline bool isContainPoint(const sf::Shape& shape, glm::fvec2 point) {
		if (shape.getPointCount() < 3) return false;

		for (int i = 0; i < shape.getPointCount(); i++) {

			glm::fvec2 point0 = applyTransform(shape.getPoint(i % shape.getPointCount()), shape);
			glm::fvec2 point1 = applyTransform(shape.getPoint((i + 1) % shape.getPointCount()), shape);
			glm::fvec2 point2 = applyTransform(shape.getPoint((i + 2) % shape.getPointCount()), shape);

			float cross0 = vectCross(point - point1, point1 - point0);
			float cross1 = vectCross(point - point2, point2 - point1);

			if (cross0 * cross1 < 0) return false;
		}
		return true;
	}

	// return if any point of shape2 is inside shape1 ?
	inline bool isShape2InShape1(const sf::Shape& shape1, const sf::Shape& shape2) {
		for (int i = 0; i < shape2.getPointCount(); i++) {
			auto shape2_point = applyTransform( shape2.getPoint(i), shape2 );
			if (isContainPoint(shape1, shape2_point)) {
				return true;
			}
		}
		return false;
	}
	inline bool isColliding(const sf::Shape& shape1, const sf::Shape& shape2) {
		bool shpae2_in_shape1 = isShape2InShape1(shape1, shape2);
		bool shpae1_in_shape2 = isShape2InShape1(shape2, shape1);
		return shpae2_in_shape1 || shpae1_in_shape2;
	}

	// TODO: interpolate vector template function

}