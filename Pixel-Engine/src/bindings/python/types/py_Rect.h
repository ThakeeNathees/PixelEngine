#pragma once

#include <pybind11/embed.h>
namespace py = pybind11;


void register_rect(py::module& m)
{
	py::class_<sf::FloatRect>(m, "Rect")
		.def(py::init<>())
		.def(py::init<float, float, float, float>())
		.def(py::init<const sf::Vector2f&, const sf::Vector2f&>())

		.def_readwrite("x", &sf::FloatRect::left)
		.def_readwrite("y", &sf::FloatRect::top)
		.def_readwrite("w", &sf::FloatRect::width)
		.def_readwrite("h", &sf::FloatRect::height)

		.def("isContain", (bool(sf::FloatRect::*)(float, float) const) & sf::FloatRect::contains)
		.def("isContain", (bool(sf::FloatRect::*)(const sf::Vector2f&) const) & sf::FloatRect::contains)
		.def("isIntersects", (bool(sf::FloatRect::*)(const sf::FloatRect & other) const) & sf::FloatRect::intersects)

		.def("__eq__", [](const sf::FloatRect& self, const sf::FloatRect& other) { return self == other; })

		;

	///////////////////////////////////////

	py::class_<sf::IntRect>(m, "Recti")
		.def(py::init<>())
		.def(py::init<int, int, int, int>())
		.def(py::init<const sf::Vector2i&, const sf::Vector2i&>())

		.def_readwrite("x", &sf::IntRect::left)
		.def_readwrite("y", &sf::IntRect::top)
		.def_readwrite("w", &sf::IntRect::width)
		.def_readwrite("h", &sf::IntRect::height)

		.def("isContain", (bool(sf::IntRect::*)(int, int) const) & sf::IntRect::contains)
		.def("isContain", (bool(sf::IntRect::*)(const sf::Vector2i&) const) & sf::IntRect::contains)
		.def("isIntersects", (bool(sf::IntRect::*)(const sf::IntRect & other) const) & sf::IntRect::intersects)

		.def("__eq__", [](const sf::IntRect& self, const sf::IntRect& other) { return self == other; })

		;
}