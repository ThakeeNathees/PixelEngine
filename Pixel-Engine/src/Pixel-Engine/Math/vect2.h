#pragma once

#ifndef PE_BUILD_DLL // else use precompiled header
	#include <iostream> 
#endif

#include "..//Core.h"


namespace PE
{
	struct PIXEL_ENGINE_API vect2
	{
		float x, y;

		vect2();
		vect2(float x, float y);

		vect2& add(const vect2& other);
		vect2& subtract(const vect2& other);
		vect2& multiply(const vect2& other);
		vect2& divide(const vect2& other);

		friend std::ostream& operator<< (std::ostream& stream, const vect2& vector);

		friend vect2 operator+(vect2 self, const vect2& other);
		friend vect2 operator-(vect2 self, const vect2& other);
		friend vect2 operator*(vect2 self, const vect2& other);
		friend vect2 operator/(vect2 self, const vect2& other);

		vect2& operator+= (const vect2& other);
		vect2& operator-= (const vect2& other);
		vect2& operator*= (const vect2& other);
		vect2& operator/= (const vect2& other);

		bool operator== (const vect2& other);
		bool operator!= (const vect2& other);

	};


}