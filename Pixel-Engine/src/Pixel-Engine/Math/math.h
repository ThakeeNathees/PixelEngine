#pragma once

#include "vect2.h"
#include "vect3.h"
#include "vect4.h"

namespace PE
{
#define PI 3.14159265358979323846
	inline float to_radians(float degrees) { return (float) degrees * (PI / 180.f); }
	inline float to_degrees(float raidans) { return (float) raidans * (180.f / PI); }
}