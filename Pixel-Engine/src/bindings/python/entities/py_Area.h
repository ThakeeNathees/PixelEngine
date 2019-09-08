#pragma once
#include "api/core.h"

#include <pybind11/embed.h>
namespace py = pybind11;

#include "api/entities/Area.h"

void register_area(py::module m)
{
	py::class_<pe::Area, sf::Transformable, pe::Asset>(m, "Area")
		.def(py::init<>())
		.def(py::init<py::str>())
		.def_static("getCount", &pe::Area::getCount)

		.def("getCentroid", &pe::Area::getCentroid, py::arg("local") = false)
		.def("isContains", (bool (pe::Area::*)(float, float)) & pe::Area::isContains)
		.def("isContains", (bool (pe::Area::*)(const sf::Vector2f&)) & pe::Area::isContains)
		.def("isConvex", &pe::Area::isConvex)
		.def("isIntersecting", &pe::Area::isIntersecting)
		.def("setShape", [](pe::Area& self, sf::Shape* shape) { self.setShape(shape); })
		.def("getShape", [](const pe::Area& self) -> sf::Shape*
			{
				if (!self.hasShape()) return nullptr;
				return &self.getShape();
			})

		.def("setPosition", (void (pe::Area::*)(float, float))&pe::Area::setPosition)
		.def("setPosition", (void (pe::Area::*)(const sf::Vector2f&))&pe::Area::setPosition)
		.def("setRotation", &pe::Area::setRotation)
		.def("setScale", (void (pe::Area::*)(float, float)) & pe::Area::setScale)
		.def("setScale", (void (pe::Area::*)(const sf::Vector2f&)) & pe::Area::setScale)
		.def("setOrigin", (void (pe::Area::*)(float, float)) & pe::Area::setOrigin)
		.def("setOrigin", (void (pe::Area::*)(const sf::Vector2f&)) & pe::Area::setOrigin)

		.def("move", (void(pe::Area::*)(float, float)) &pe::Area::move )
		.def("move", (void(pe::Area::*)(const sf::Vector2f&)) &pe::Area::move )
		.def("rotate", &pe::Area::rotate)
		.def("scale", (void(pe::Area::*)(float, float)) & pe::Area::scale)
		.def("scale", (void(pe::Area::*)(const sf::Vector2f&)) & pe::Area::scale)
		;		
}
