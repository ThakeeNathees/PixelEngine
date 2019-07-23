#pragma once

#ifndef PE_BUILD_DLL // else use precompiled header
#include <iostream> 
#endif

#include "../Core.h"

namespace PE
{
	struct PIXEL_ENGINE_API vect3
	{
		float x, y, z;

		vect3();
		vect3(float x, float y, float z);

		vect3& add(const vect3& other);
		vect3& subtract(const vect3& other);
		vect3& multiply(const vect3& other);
		vect3& divide(const vect3& other);

		friend std::ostream& operator<< (std::ostream& stream, const vect3& vector);

		friend vect3 operator+(vect3 self, const vect3& other);
		friend vect3 operator-(vect3 self, const vect3& other);
		friend vect3 operator*(vect3 self, const vect3& other);
		friend vect3 operator/(vect3 self, const vect3& other);

		vect3& operator+= (const vect3& other);
		vect3& operator-= (const vect3& other);
		vect3& operator*= (const vect3& other);
		vect3& operator/= (const vect3& other);

		bool operator== (const vect3& other);
		bool operator!= (const vect3& other);

	};


}