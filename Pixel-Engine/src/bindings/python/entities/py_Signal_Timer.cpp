#pragma once
#include "pch.h"
#include "entities.h"

#include <pybind11/stl.h>
#include <pybind11/embed.h>
namespace py = pybind11;

#include "api/Application.h"



void register_signal_timer(py::module& m)
{

	py::class_<pe::Signal>(m, "Signal", py::dynamic_attr())
		.def(py::init<>())
		.def(py::init<py::str>())
		.def_static("getCount", pe::Signal::getCount)

		.def("setName", [](pe::Signal& self, const std::string& name) {self.setName(name); })
		.def("getName", [](pe::Signal& self) {return self.getName(); }, py::return_value_policy::reference)
		.def("clear", [](pe::Signal& self) {self.clear(); })

		
		.def("addReciever", [](pe::Signal& self, pe::Object* obj) {self.addReciever(obj); })
		.def("getRecievers", [](pe::Signal& self) {return self.getRecievers(); }, py::return_value_policy::reference)
		.def("getSender", [](pe::Signal& self) -> pe::Object*
			{
				if (!self.hasSender()) return nullptr;
				else return &self.getSender();
			}
			, py::return_value_policy::reference
		)
		;

	////////////////////////////////////////////////////////////

	py::class_<pe::Timer>(m, "Timer")
		.def(py::init<>())
		.def(py::init<py::str>())

		.def("setName", [](pe::Timer& self, const std::string& name) {self.setName(name); })
		.def("start", [](pe::Timer& self) {self.start(); })
		.def("stop", [](pe::Timer& self) {self.stop(); })
		.def("setLoop", [](pe::Timer& self, bool loop) {self.setLoop(loop); })
		.def("setTime", [](pe::Timer& self, float time) {self.setTime(time); })
		.def("getTime", [](pe::Timer& self) {return self.getTime(); })
		.def("getRemainingTime", [](pe::Timer& self) {return self.getRemainingTime(); })
		.def("getTimeoutSignal", [](pe::Timer& self) {return self.getTimeoutSignal(); }, py::return_value_policy::reference)

		//.def("setScene", [](pe::Timer& self, pe::Scene* scene) {self.setScene(scene); })
		;
}
