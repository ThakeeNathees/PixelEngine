#pragma once

#include "core/internal.h"
#include "core/error.h"

#define VECT2_DEFAULT_CMP_OP_OVERLOAD(m_op)                         \
FORCE_INLINE bool operator m_op (const Vec_<T>& p_other) const {    \
	return get_length() m_op p_other.get_length();                  \
}

template<typename T>
struct Vec_ {
	union { T x, w; };
	union { T y, h; };

	// Constructors
	Vec_(T p_x = 0, T p_y = 0) : x(p_x), y(p_y) {}
	template<typename T2>
	Vec_(const Vec_<T2>& p_copy) : x((T)p_copy.x), y((T)p_copy.y) {}

	// Methods.
	FORCE_INLINE double get_length() const {
		return (double)sqrtf((double)(x * x + y * y));
	}
	FORCE_INLINE float get_angle() const {
		if (x == 0) return (float)M_PI_2;
		return atanf(y / x);
	}
	FORCE_INLINE bool is_empty() const {
		return x == 0 && y == 0;
	}

	// Operators.
	FORCE_INLINE Vec_<T> operator+(const Vec_<T>& p_other) const {
		return Vec_<T>(x + p_other.x, y + p_other.y);
	}
	FORCE_INLINE Vec_<T> operator-(const Vec_<T>& p_other) const {
		return Vec_<T>(x - p_other.x, y - p_other.y);
	}
	FORCE_INLINE Vec_<T> operator*(const Vec_<T>& p_other) const {
		return Vec_<T>(x * p_other.x, y * p_other.y);
	}
	template <typename T2>
	FORCE_INLINE Vec_<T> operator*(T2 p_val) const {
		return Vec_<T>(x * p_val, y * p_val);
	}
	FORCE_INLINE Vec_<T> operator/(const Vec_<T>& p_other) const {
		if (p_other.x == 0 || p_other.y == 0)
			throw VarError(VarError::ZERO_DIVISION, "");
		return Vec_<T>(x / p_other.x, y / p_other.y);
	}

	VECT2_DEFAULT_CMP_OP_OVERLOAD(< );
	VECT2_DEFAULT_CMP_OP_OVERLOAD(<= );
	VECT2_DEFAULT_CMP_OP_OVERLOAD(> );
	VECT2_DEFAULT_CMP_OP_OVERLOAD(>= );
	FORCE_INLINE bool operator==(const Vec_<T>& p_other) const {
		return x == p_other.x && y == p_other.y;
	}
	FORCE_INLINE bool operator!=(const Vec_<T>& p_other) const {
		return !operator==(p_other);
	}

	FORCE_INLINE Vec_<T>& operator+=(const Vec_<T>& p_other) {
		x += p_other.x; y += p_other.y;
		return *this;
	}
	FORCE_INLINE Vec_<T>& operator-=(const Vec_<T>& p_other) {
		x -= p_other.x; y -= p_other.y;
		return *this;
	}

	FORCE_INLINE Vec_<T>& operator*=(const Vec_<T>& p_other) {
		x *= p_other.x; y *= p_other.y;
		return *this;
	}

	FORCE_INLINE Vec_<T>& operator/=(const Vec_<T>& p_other) {
		if (p_other.x == 0 || p_other.y == 0)
			throw VarError(VarError::ZERO_DIVISION, "");
		x /= p_other.x; y /= p_other.y;
		return *this;
	}

	FORCE_INLINE operator bool() const { return x == 0 && y == 0; }

	String to_string() const {
		return String("Vect2(")
			+ std::to_string(x) + ", "
			+ std::to_string(y) + ")";
	}
};



typedef Vec_<float> Vec;
typedef Vec_<int> iVec;

typedef Vec  Size;
typedef Vec  Point;
typedef iVec iSize;
typedef iVec iPoint;

template<typename T>
std::ostream& operator<<(std::ostream& p_ostream, const Vec_<T>& p_vect) {
	p_ostream << p_vect.to_string();
	return p_ostream;
}

