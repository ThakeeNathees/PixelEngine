#include "pepch.h"
#include "vect4.h"

namespace PE
{
	vect4::vect4() {
		x = .0f;
		y = .0f;
		z = .0f;
		w = .0f;
	}

	vect4::vect4(float x, float y, float z, float w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	vect4& vect4::add(const vect4& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;
		return (*this);
	}

	vect4& vect4::subtract(const vect4& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;
		return (*this);
	}

	vect4& vect4::multiply(const vect4& other) {
		x *= other.x;
		y *= other.y;
		z *= other.z;
		w *= other.w;
		return (*this);
	}

	vect4& vect4::divide(const vect4& other) {
		x /= other.x;
		y /= other.y;
		z /= other.z;
		w /= other.w;
		return (*this);
	}

	std::ostream& operator<< (std::ostream& stream, const vect4& vector) {
		stream << "vect4( " << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << " )";
		return stream;
	}

	vect4 operator+ (vect4 self, const vect4& other) {
		return self.add(other);
	}

	vect4 operator- (vect4 self, const vect4& other) {
		return self.subtract(other);
	}

	vect4 operator* (vect4 self, const vect4& other) {
		return self.multiply(other);
	}

	vect4 operator/ (vect4 self, const vect4& other) {
		return self.divide(other);
	}

	vect4& vect4::operator+= (const vect4& other) {
		add(other);
		return (*this);
	}

	vect4& vect4::operator-= (const vect4& other) {
		subtract(other);
		return (*this);
	}

	vect4& vect4::operator*= (const vect4& other) {
		multiply(other);
		return (*this);
	}

	vect4& vect4::operator/= (const vect4& other) {
		divide(other);
		return (*this);
	}

	bool vect4::operator== (const vect4& other) {
		return (this->x == other.x) && (this->y == other.y) && (this->z == z) && (this->w == w);
	}

	bool vect4::operator!= (const vect4& other) {
		return !(*(this) == other);
	}

}
