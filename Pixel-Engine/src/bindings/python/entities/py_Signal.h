#pragma once

#include <pybind11/stl.h>
#include <pybind11/embed.h>
namespace py = pybind11;

#include "api/entities/Signal.h"

#include "SFML/Window.hpp"
void register_signal(py::module m)
{

	py::class_<pe::Signal>(m, "Signal")
		.def(py::init<>())
		.def(py::init<py::str>())
		.def_static("getCount", &pe::Signal::getCount)

		.def("setName", &pe::Signal::setName)
		.def("getName", &pe::Signal::getName)
		.def("clear", &pe::Signal::clear)

		//.def("setData", [](pe::Signal& self, py::object* data) { self.setData(data); })
		//.def("getData", [](pe::Signal& self) { return self.getData<py::object*>(); })

		/*
		.def("addReciever", &pe::Signal::addReciever)
		.def("getRecievers", &pe::Signal::getRecievers)
		.def("getSender", [](pe::Signal& self) -> pe::Object*
			{
				if (!self.hasSender()) return nullptr;
				else return &self.getSender();
			}
		)
		*/
		;
}
