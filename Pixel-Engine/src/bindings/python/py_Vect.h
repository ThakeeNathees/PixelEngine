#pragma once
#include "pybind.h"

#include "glm.hpp"
struct py_Vect
{
	double _x, _y;

	py_Vect() : _x(0), _y(0) {}
	py_Vect(double x, double y): _x(x), _y(y) {}
	
	
	const py::str str() const {
		return py::str( std::string("(").append(std::to_string(_x)).append(", ").append(std::to_string(_y)).append(")").c_str() );
	}

	py_Vect operator+(const py_Vect& other) {
		return py_Vect(_x + other._x, _y + other._y );
	}
	py_Vect operator-(const py_Vect& other) {
		return py_Vect(_x - other._x, _y - other._y );
	}
	py_Vect operator*(const py_Vect& other) {
		return py_Vect(_x * other._x, _y * other._y );
	}
	py_Vect operator*(double x) {
		return py_Vect(x * _x, x * _y);
	}
	py_Vect operator/(double x) {
		return py_Vect( _x/x, _y/x );
	}

	py_Vect* operator+=(const py_Vect& other) {
		_x += other._x; _y += other._y; return this;
	}
	py_Vect* operator-=(const py_Vect& other) {
		_x -= other._x; _y -= other._y; return this;
	}
	py_Vect* operator*=(const py_Vect& other) {
		_x *= other._x; _y *= other._y; return this;
	}
	py_Vect* operator*=(double x) {
		_x *= x; _y *= x; return this;
	}

	py_Vect* operator/=(double x) {
		_x /= x; _y /= x; return this;
	}

	bool operator==(const py_Vect& other) {
		return (_x == other._x && _y == other._y);
	}
};

void register_vect(py::module& m) 
{
	py::class_<py_Vect>(m, "Vect")
		.def(py::init<>())
		.def(py::init<double, double>())
		.def_readwrite("x", &py_Vect::_x)
		.def_readwrite("y", &py_Vect::_y)

		.def("__str__", &py_Vect::str, "some help")

		.def("__add__", &py_Vect::operator+)
		.def("__sub__", &py_Vect::operator-)
		.def("__mul__", ( py_Vect(py_Vect::*)(const py_Vect&) ) &py_Vect::operator*  )
		.def("__mul__", ( py_Vect(py_Vect::*)(double) ) &py_Vect::operator*)
		.def("__rmul__", ( py_Vect(py_Vect::*)(double) ) &py_Vect::operator*)
		.def("__div__", &py_Vect::operator/)

		.def("__iadd__", &py_Vect::operator+=)
		.def("__isub__", &py_Vect::operator-=)
		.def("__imul__", ( py_Vect*(py_Vect::*)(const py_Vect&) ) &py_Vect::operator*=)
		.def("__imul__", ( py_Vect*(py_Vect::*)(double) ) &py_Vect::operator*=)
		.def("__idiv__", &py_Vect::operator/=)
		.def("__eq__", &py_Vect::operator==)
		;
}