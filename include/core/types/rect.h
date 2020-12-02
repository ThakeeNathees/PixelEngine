#pragma once

#include "core/internal.h"
#include "core/error.h"
#include "vec.h"

template <typename T>
struct Rect_ {
public:
	T x, y;
	T w, h;

	// Constructors
	Rect_(T _x = 0, T _y = 0, T _w = 0, T _h = 0) : x(_x), y(_y), w(_w), h(_h) {}
	template<typename T1, typename T2>
	Rect_(Vec_<T1> position, Vec_<T2> size) : x(position.x), y(position.y), w(size.w), h(size.h) {}
	template<typename T2> Rect_(const Rect_<T2>& copy) :
		x((T)copy.x), y((T)copy.y), w((T)copy.w), h((T)copy.h) {}

	// Methods
	template <typename T2>
	FORCE_INLINE bool point_in(Vec_<T2> p) const {
		return ((p.x >= x) && (p.x < (x + w)) && (p.y >= y) && (p.y < (y + h)));
	}

	FORCE_INLINE bool is_empty() const {
		return (w == 0) || (h == 0);
	}

	// Operators
	template<typename T2>
	FORCE_INLINE bool operator==(const Rect_<T2>& p_other) const {
		return x == p_other.x && y == p_other.y && w == p_other.w && h == p_other.h;
	}

	// TODO: implement wrapper methods for SDL rect
};

typedef Rect_<int> iRect;
typedef Rect_<float> Rect;