#pragma once

#include "core/internal.h"
#include "core/error.h"

struct Color {
	Color(uint8_t _r = 0, uint8_t _g = 0, uint8_t _b = 0, uint8_t _a = 0)
		:r(_r), g(_g), b(_b), a(_a) {}
	Color(float _r, float _g, float _b, float _a = 1.0f)
		:r((uint8_t)(_r * 255)), g((uint8_t)(_g * 255)), b((uint8_t)(_b * 255)), a((uint8_t)(_a * 255)) {}

	uint8_t r, g, b, a;
};
