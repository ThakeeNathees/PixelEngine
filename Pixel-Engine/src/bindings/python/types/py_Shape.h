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

		.def("getPointCount", &sf::Shape::getPointCount)
		.def("getPoint", &sf::Shape::getPoint)
		.def("getLocalBounds", &sf::Shape::getLocalBounds)
		.def("getGlobalBounds", &sf::Shape::getGlobalBounds)
		;

	py::class_<sf::ConvexShape, sf::Shape>(m, "ConvexShape")
		.def(py::init<std::size_t>(), py::arg("point_count") = 0)
		.def("setPointCount", &sf::ConvexShape::setPointCount)
		.def("setPoint", &sf::ConvexShape::setPoint)
		;
	py::class_<sf::RectangleShape, sf::Shape>(m, "RectangleShape")
		.def(py::init<const sf::Vector2f&>(), py::arg("size")=sf::Vector2f(0,0))
		.def("setSize", &sf::RectangleShape::setSize)
		.def("getSize", &sf::RectangleShape::getSize)
		;
	py::class_<sf::CircleShape, sf::Shape>(m, "CircleShape")
		.def(py::init<float, std::size_t>(), py::arg("radius") = 0, py::arg("point_count") = 30)
		.def("setRadius", &sf::CircleShape::setRadius)
		.def("getRadius", &sf::CircleShape::getRadius)
		.def("setPointCount", &sf::CircleShape::setPointCount)
		.def("getPointCount", &sf::CircleShape::getPointCount)
		;
}
