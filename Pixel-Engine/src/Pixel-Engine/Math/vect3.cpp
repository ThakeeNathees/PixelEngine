#include "pepch.h"
#include "vect3.h"

namespace PE
{
	vect3::vect3(){
		x = .0f;
		y = .0f;
		z = .0f;
	}

	vect3::vect3(float x, float y, float z){
		this->x = x;
		this->y = y;
		this->z = z;
	}

	vect3& vect3::add(const vect3& other){
		x += other.x;
		y += other.y;
		z += other.z;
		return (*this);
	}

	vect3& vect3::subtract(const vect3& other){
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return (*this);
	}
	
	vect3& vect3::multiply(const vect3& other){
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return (*this);
	}
	
	vect3& vect3::divide(const vect3& other) {
		x /= other.x;
		y /= other.y;
		z /= other.z;
		return (*this);
	}

	std::ostream& operator<< (std::ostream& stream, const vect3& vector){
		stream << "vect3( " << vector.x << ", " << vector.y << ", " << vector.z <<  " )";
		return stream;
	}

	vect3 operator+ (vect3 self, const vect3& other) {
		return self.add(other);
	}

	vect3 operator- (vect3 self, const vect3& other) {
		return self.subtract(other);
	}

	vect3 operator* (vect3 self, const vect3& other) {
		return self.multiply(other);
	}

	vect3 operator/ (vect3 self, const vect3& other) {
		return self.divide(other);
	}

	vect3& vect3::operator+= (const vect3& other) {
		add(other);
		return (*this);
	}

	vect3& vect3::operator-= (const vect3& other) {
		subtract(other);
		return (*this);
	}

	vect3& vect3::operator*= (const vect3& other) {
		multiply(other);
		return (*this);
	}

	vect3& vect3::operator/= (const vect3& other) {
		divide(other);
		return (*this);
	}

	bool vect3::operator== (const vect3& other) {
		return (this->x == other.x) && (this->y == other.y) && (this->z ==z) ;
	}
	
	bool vect3::operator!= (const vect3& other) {
		return !(*(this)==other);
	}

}
