#pragma once

#ifndef PE_BUILD_DLL // else use precompiled header
#include <iostream> 
#endif

#include "..//Core.h"

namespace PE
{
	struct PIXEL_ENGINE_API vect4
	{
		float x, y, z, w;

		vect4();
		vect4(float x, float y, float z, float w);

		vect4& add(const vect4& other);
		vect4& subtract(const vect4& other);
		vect4& multiply(const vect4& other);
		vect4& divide(const vect4& other);

		friend std::ostream& operator<< (std::ostream& stream, const vect4& vector);

		friend vect4 operator+(vect4 self, const vect4& other);
		friend vect4 operator-(vect4 self, const vect4& other);
		friend vect4 operator*(vect4 self, const vect4& other);
		friend vect4 operator/(vect4 self, const vect4& other);

		vect4& operator+= (const vect4& other);
		vect4& operator-= (const vect4& other);
		vect4& operator*= (const vect4& other);
		vect4& operator/= (const vect4& other);

		bool operator== (const vect4& other);
		bool operator!= (const vect4& other);

	};


}