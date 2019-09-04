#pragma once

#include <pybind11/embed.h>
namespace py = pybind11;

struct py_Vect : public sf::Vector2f
{
	py_Vect( const sf::Vector2f& vect ): sf::Vector2f(vect) {}

	// python functions
	py_Vect() :sf::Vector2f(0,0) {}
	py_Vect(float _x, float _y): sf::Vector2f(_x, _y) {}
	
	const py::str py_str() const {
		return py::str( std::string("(").append(std::to_string(x)).append(", ").append(std::to_string(y)).append(")").c_str() );
	}

	py_Vect operator+(const py_Vect& other) const {
		return py_Vect(x + other.x, y + other.y );
	}
	py_Vect operator-(const py_Vect& other) const {
		return py_Vect(x - other.x, y - other.y );
	}
	py_Vect operator*(const py_Vect& other) const {
		return py_Vect(x * other.x, y * other.y );
	}
	py_Vect operator*(float n) const {
		return py_Vect(n * x, n * y);
	}
	py_Vect operator/(float n) const {
		return py_Vect( x/n, y/n );
	}

	py_Vect* operator+=(const py_Vect& other) {
		x += other.x; y += other.y; return this;
	}
	py_Vect* operator-=(const py_Vect& other) {
		x -= other.x; y -= other.y; return this;
	}
	py_Vect* operator*=(const py_Vect& other) {
		x *= other.x; y *= other.y; return this;
	}
	py_Vect* operator*=(float n) {
		x *= n; y *= n; return this;
	}

	py_Vect* operator/=(float n) {
		x /= n; y /= n; return this;
	}

	bool operator==(const py_Vect& other) {
		return (x == other.x && y == other.y);
	}
};

void register_vect(py::module& m) 
{
	py::class_<py_Vect>(m, "Vect")
		.def(py::init<>())
		.def(py::init<float, float>())
		.def_readwrite("x", &py_Vect::x)
		.def_readwrite("y", &py_Vect::y)

		.def("__str__", &py_Vect::py_str)

		.def("__add__", &py_Vect::operator+)
		.def("__sub__", &py_Vect::operator-)
		.def("__mul__", ( py_Vect(py_Vect::*)(const py_Vect&) const) &py_Vect::operator*  )
		.def("__mul__", ( py_Vect(py_Vect::*)(float) const) &py_Vect::operator*)
		.def("__rmul__", ( py_Vect(py_Vect::*)(float) const) &py_Vect::operator*)
		.def("__div__", &py_Vect::operator/)

		.def("__iadd__", &py_Vect::operator+=)
		.def("__isub__", &py_Vect::operator-=)
		.def("__imul__", ( py_Vect*(py_Vect::*)(const py_Vect&) ) &py_Vect::operator*=)
		.def("__imul__", ( py_Vect*(py_Vect::*)(float) ) &py_Vect::operator*=)
		.def("__idiv__", &py_Vect::operator/=)
		.def("__eq__", &py_Vect::operator==)
		;
}