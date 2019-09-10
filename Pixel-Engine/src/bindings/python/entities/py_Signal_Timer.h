#pragma once

#include <pybind11/stl.h>
#include <pybind11/embed.h>
namespace py = pybind11;

#include "api/entities/Signal.h"
#include "api/entities/Timer.h"

#include "SFML/Window.hpp"

void register_signal_timer(py::module& m)
{

	py::class_<pe::Signal>(m, "Signal", py::dynamic_attr())
		.def(py::init<>())
		.def(py::init<py::str>())
		.def_static("getCount", pe::Signal::getCount)

		.def("setName", &pe::Signal::setName)
		.def("getName", &pe::Signal::getName)
		.def("clear", &pe::Signal::clear)

		
		.def("addReciever", &pe::Signal::addReciever)
		.def("getRecievers", &pe::Signal::getRecievers)
		.def("getSender", [](pe::Signal& self) -> pe::Object*
			{
				if (!self.hasSender()) return nullptr;
				else return &self.getSender();
			}
		)
		;

	////////////////////////////////////////////////////////////

	py::class_<pe::Timer>(m, "Timer")
		.def(py::init<>())
		.def(py::init<py::str>())

		.def("setName", &pe::Timer::setName)
		.def("start", &pe::Timer::start)
		.def("stop", &pe::Timer::stop)
		.def("setLoop", &pe::Timer::setLoop)
		.def("setTime", &pe::Timer::setTime)
		.def("getTime", &pe::Timer::getTime)
		.def("getRemainingTime", &pe::Timer::getRemainingTime)
		.def("getTimoutSignal", &pe::Timer::getTimoutSignal)

		.def("setScene", &pe::Timer::setScene)
		;
}
