#pragma once

#include <pybind11/embed.h>
namespace py = pybind11;

#include "py_Rect.h"

class py_Shape : public sf::ConvexShape
{
public:

	py_Shape(int point_count) : sf::ConvexShape(point_count) {}
	py_Vect py_getPoint(int index) const { return getPoint(index);  } // TODO: throw index out of bound
	void py_setPoint(int index, const py_Vect& point) { setPoint(index, point); }
};

void register_shape(py::module& m)
{
	py::class_<py_Shape>(m, "Shape")
		.def(py::init<int>())
		.def("setPointCount", &py_Shape::setPointCount)
		.def("setPoint", &py_Shape::py_setPoint)

		.def("getPoint", &py_Shape::py_getPoint)
		.def("getPointCount", &py_Shape::getPointCount)
		;
}