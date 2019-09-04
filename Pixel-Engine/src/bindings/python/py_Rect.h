#pragma once

#include <pybind11/embed.h>
namespace py = pybind11;

#include "py_Vect.h"

struct py_Rect
{
	float x, y, w, h;

	py_Rect() : x(0), y(0), w(0), h(0) {}
	py_Rect(float _x, float _y, float _w, float _h) : x(_x), y(_y), w(_w), h(_h) {}
	py_Rect(const py_Vect& position, const py_Vect& size) : x(position.x), y(position.y), w(size.x), h(size.y) {}

	bool isContain(float _x, float _y) const {
		return (x <= _x && _x <= x + w) && (y <= _y && _y <= y + h);
	}
	bool isContain(const py_Vect& point) const {
		return (x <= point.x && point.x <= x + w) && (y <= point.y && point.y <= y + h);
	}

	bool isIntersects(const py_Rect& other) {
		if (other.x + other.w < x || x + w < other.x) return false;
		if (other.y + other.h < y || y + h < other.y) return false;
		return true;
	}
};

void register_rect(py::module& m)
{
	py::class_<py_Rect>(m, "Rect")
		.def(py::init<>())
		.def(py::init<float, float, float, float>())
		.def(py::init<const py_Vect&, const py_Vect&>())

		.def_readwrite("x",&py_Rect::x)
		.def_readwrite("y",&py_Rect::y)
		.def_readwrite("w",&py_Rect::w)
		.def_readwrite("h",&py_Rect::h)

		.def("isContain", (bool(py_Rect::*)(float, float) const) &py_Rect::isContain)
		.def("isContain", (bool(py_Rect::*)(const py_Vect&) const) &py_Rect::isContain)
		.def("isIntersects", &py_Rect::isIntersects)
		;
}
