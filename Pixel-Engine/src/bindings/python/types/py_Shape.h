#pragma once

#include <pybind11/embed.h>
namespace py = pybind11;



void register_shape(py::module& m)
{
	py::class_<sf::Shape, sf::Drawable, sf::Transformable>(m, "Shape")

		.def("setTexture", &sf::Shape::setTexture, py::arg("texture"), py::arg("resetrect") = false)
		.def("setTextureRect", &sf::Shape::setTextureRect)
		.def("setFillColor", &sf::Shape::setFillColor)
		.def("setOutlineColor", &sf::Shape::setOutlineColor)
		.def("setOutlineThickness", &sf::Shape::setOutlineThickness)

		.def("getTexture", &sf::Shape::getTexture)
		.def("getTextureRect", &sf::Shape::getTextureRect)
		.def("getFillColor", &sf::Shape::getFillColor)
		.def("getOutlineColor", &sf::Shape::getOutlineColor)
		.def("getOutlineThickness", &sf::Shape::getOutlineThickness)

		.def("getPointCount", [](sf::Shape& self) -> int { return self.getPointCount(); })
		.def("getPoint", [](sf::Shape& self, int index) -> sf::Vector2f { return self.getPoint(index); })
		.def("getLocalBounds", &sf::Shape::getLocalBounds)
		.def("getGlobalBounds", &sf::Shape::getGlobalBounds)

		;
}
