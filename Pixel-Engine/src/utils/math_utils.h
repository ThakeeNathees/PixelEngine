#pragma once
#include "..//api/core.h"


#define PI 3.141592654

namespace pe
{
	template<typename T=glm::fvec2>
	inline glm::fvec2 rotatePoint( float x, float y, float angle_degree ) {
		float angle = angle_degree * PI / 180.0;
		glm::fvec2 rotated;
		rotated.x = x * glm::cos(angle) - y * glm::sin( angle );
		rotated.y = y * glm::cos(angle) + x * glm::sin(angle);
		return rotated;
	}
	inline glm::fvec2 rotatePoint(glm::fvec2 point, float angle_degree) { return rotatePoint(point.x, point.y, angle_degree); }
	inline glm::fvec2 rotatePoint(sf::Vector2f point, float angle_degree) { return rotatePoint(point.x, point.y, angle_degree); }

	template <typename V1, typename V2>
	V2 convertVector(V1 vec) {
		V2 vect;
		vect.x = vec.x;
		vect.y = vec.y;
		return vect;
	}


}
