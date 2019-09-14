#include "pch.h"
#include "pe_api.h"

#include "api/Scene.h"

void register_scene(py::module& m)
{
	py::class_<pe::Scene, pe::Asset>(m, "Scene")
		.def(py::init<>())
		.def(py::init<const std::string&>())

		.def("addObject", &pe::Scene::addObject, py::return_value_policy::reference)
		.def("addSignal", &pe::Scene::addSignal, py::return_value_policy::reference)
		.def("addTimer", &pe::Scene::addTimer, py::return_value_policy::reference)
		.def("clear", &pe::Scene::clear, py::return_value_policy::reference)
		.def("getBackground", &pe::Scene::getBackground, py::return_value_policy::reference)
		//.def("getDrawables", &pe::Scene::getDrawables)
		.def("getId", &pe::Scene::getId)
		.def("getName", &pe::Scene::getName)
		.def("getObject", &pe::Scene::getObject, py::return_value_policy::reference)
		.def("getObjects", &pe::Scene::getObjects, py::return_value_policy::reference)
		.def("setBackground", &pe::Scene::setBackground, py::return_value_policy::reference)

		;
}