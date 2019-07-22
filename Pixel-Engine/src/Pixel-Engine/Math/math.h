#pragma once

#include "vect2.h"
#include "vect3.h"
#include "vect4.h"

namespace PE
{
#define PI 3.14159265358979323846
	inline double to_radians(float degrees) { return degrees * (PI / 180.0); }
	inline double to_degrees(float raidans) { return raidans * (180.0 / PI); }
}