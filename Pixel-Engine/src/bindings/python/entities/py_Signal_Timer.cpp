#pragma once
#include "pch.h"
#include "entities.h"

#include <pybind11/stl.h>
#include <pybind11/embed.h>
namespace py = pybind11;

#include "api/Application.h"



void register_signal_timer(py::module& m)
{

	py::class_<pe::Signal>py_signal(m, "Signal", py::dynamic_attr());

	py::enum_<pe::Signal::Type>(py_signal, "Type")
		.value("CUSTOM", pe::Signal::Type::CUSTOM)
		.value("ANIMATION_END", pe::Signal::Type::ANIMATION_END)
		.value("SCENE_CHANGE", pe::Signal::Type::SCENE_CHANGE)
		;
	py::class_<pe::Signal::_AnimEndSignal>(py_signal, "_AnimEndSignal")
		.def_readonly("anim_id", &pe::Signal::_AnimEndSignal::anim_id)
		.def_readonly("anim_name", &pe::Signal::_AnimEndSignal::anim_name)
		;
	py::class_<pe::Signal::_SceneChange>(py_signal, "_SceneChange")
		.def_readonly("scene_id", &pe::Signal::_SceneChange::scene_id)
		.def_readonly("scene_name", &pe::Signal::_SceneChange::scene_name)
		;

	py_signal
		.def(py::init<>())
		.def(py::init<py::str>())
		.def_static("getCount", pe::Signal::getCount)

		.def("getType", &pe::Signal::getType)
		.def_readonly("anim_end_data", &pe::Signal::anim_end_data)
		.def_readonly("scene_change_data", &pe::Signal::scene_change_data)

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
