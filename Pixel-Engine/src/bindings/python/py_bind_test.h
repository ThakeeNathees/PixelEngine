#pragma once

#include "api/core.h"

#include <pybind11/embed.h>
namespace py = pybind11;

class T { public: int x; };
class Tuser { 
public:  
	T* callWithT(T* t) {
		std::cout << "[cpp] called with t, t.x = " << t->x << std::endl;
		t->x = 2 * t->x;
		return t;
	}
};

PYBIND11_EMBEDDED_MODULE(pixel_engine, m) {
	py::class_<T>(m, "T")
		.def(py::init<>())
		.def_readwrite("x",&T::x)
		;
	py::class_<Tuser>(m, "Tuser")
		.def(py::init<>())
		.def("callWithT",&Tuser::callWithT)
		;
}
