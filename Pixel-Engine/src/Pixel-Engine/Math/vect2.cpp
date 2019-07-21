#include "pepch.h"

#include "vect2.h"

namespace PE
{
	vect2::vect2(){
		x = .0f;
		y = .0f;
	}

	vect2::vect2(float x, float y){
		this->x = x;
		this->y = y;
	}

	vect2& vect2::add(const vect2& other){
		x += other.x;
		y += other.y;
		return (*this);
	}

	vect2& vect2::subtract(const vect2& other){
		x -= other.x;
		y -= other.y;
		return (*this);
	}
	
	vect2& vect2::multiply(const vect2& other){
		x *= other.x;
		y *= other.y;
		return (*this);
	}
	
	vect2& vect2::divide(const vect2& other) {
		x /= other.x;
		y /= other.y;
		return (*this);
	}

	std::ostream& operator<< (std::ostream& stream, const vect2& vector){
		stream << "vect2( " << vector.x << ", " << vector.y << " )";
		return stream;
	}

	vect2 operator+ (vect2 self, const vect2& other) {
		return self.add(other);
	}

	vect2 operator- (vect2 self, const vect2& other) {
		return self.subtract(other);
	}

	vect2 operator* (vect2 self, const vect2& other) {
		return self.multiply(other);
	}

	vect2 operator/ (vect2 self, const vect2& other) {
		return self.divide(other);
	}

	vect2& vect2::operator+= (const vect2& other) {
		add(other);
		return (*this);
	}

	vect2& vect2::operator-= (const vect2& other) {
		subtract(other);
		return (*this);
	}

	vect2& vect2::operator*= (const vect2& other) {
		multiply(other);
		return (*this);
	}

	vect2& vect2::operator/= (const vect2& other) {
		divide(other);
		return (*this);
	}

	bool vect2::operator== (const vect2& other) {
		return (this->x == other.x) && (this->y == other.y);
	}
	
	bool vect2::operator!= (const vect2& other) {
		return !(*(this)==other);
	}

}
