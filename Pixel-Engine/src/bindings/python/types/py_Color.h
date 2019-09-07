#pragma once

#include <pybind11/embed.h>
namespace py = pybind11;


void register_color(py::module m)
{
	py::class_<sf::Color>(m, "Color")
		.def(py::init<>())
		.def(py::init<int, int, int, int>(), py::arg("r")=0, py::arg("g") = 0, py::arg("b") = 0, py::arg("a") = 255)

		.def_readwrite("r",&sf::Color::r)
		.def_readwrite("g",&sf::Color::g)
		.def_readwrite("b",&sf::Color::b)
		.def_readwrite("a",&sf::Color::a)

		.def_readonly_static("Black",		&sf::Color::Black)
		.def_readonly_static("White",		&sf::Color::White)
		.def_readonly_static("Red",			&sf::Color::Red)
		.def_readonly_static("Green",		&sf::Color::Green)
		.def_readonly_static("Blue",		&sf::Color::Blue)
		.def_readonly_static("Yellow",		&sf::Color::Yellow)
		.def_readonly_static("Magenta",		&sf::Color::Magenta)
		.def_readonly_static("Cyan",		&sf::Color::Cyan)
		.def_readonly_static("Transparent", &sf::Color::Transparent)

		.def("__str__", [](const sf::Color& self) -> py::str
			{
				py::str _ret;
				_ret = std::string("(")
					.append("r=").append(std::to_string(self.r)).append(", ")
					.append("g=").append(std::to_string(self.g)).append(", ")
					.append("b=").append(std::to_string(self.b)).append(", ")
					.append("a=").append(std::to_string(self.a)).append(")");
				return _ret;
			})
		.def("__eq__", [](const sf::Color& self, const sf::Color& other) { return self == other; })
		.def("__add__", [](const sf::Color& self, const sf::Color& other) -> sf::Color { return self + other; })
		.def("__sub__", [](const sf::Color& self, const sf::Color& other) ->sf::Color { return self - other; })
		.def("__mul__", [](const sf::Color& self, const sf::Color& other) -> sf::Color { return self * other; })
		;
}
