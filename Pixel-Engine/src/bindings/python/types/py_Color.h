#pragma once

#include <pybind11/embed.h>
namespace py = pybind11;

struct py_Color : public sf::Color
{
	py_Color() : sf::Color() {}
	py_Color(const sf::Color& color) : sf::Color(color) {}
	py_Color(int r, int g, int b, int a = 255) : sf::Color(r, g, b, a) {}

	const py::str py_str() const {
		return py::str(std::string("(")
			.append(std::to_string(r)).append(", ")
			.append(std::to_string(g)).append(", ")
			.append(std::to_string(b)).append(", ")
			.append(std::to_string(a))
			.append(")").c_str());
	}

	bool operator==(const py_Color& other) { return (sf::Color)(*this) == (sf::Color)(other); }

	py_Color operator+(const py_Color& other) { return (py_Color) ((sf::Color) * this + (sf::Color)other); }
	py_Color operator-(const py_Color& other) { return (py_Color)((sf::Color) * this - (sf::Color)other); }
	py_Color operator*(const py_Color& other) { return (py_Color)((sf::Color) * this * (sf::Color)other); }

	py_Color* operator+=(const py_Color& other){ *this = ((sf::Color) * this) + ((sf::Color)other); return this; }
	py_Color* operator-=(const py_Color& other){ *this = ((sf::Color) * this) - ((sf::Color)other); return this; }
	py_Color* operator*=(const py_Color& other){ *this = ((sf::Color) * this) * ((sf::Color)other); return this; }
};

void register_color(py::module m)
{
	py::class_<py_Color>(m, "Color")
		.def(py::init<>())
		.def(py::init<int, int, int, int>(), py::arg("r")=0, py::arg("g") = 0, py::arg("b") = 0, py::arg("a") = 255)

		.def_readwrite("r",&py_Color::r)
		.def_readwrite("g",&py_Color::g)
		.def_readwrite("b",&py_Color::b)
		.def_readwrite("a",&py_Color::a)

		.def_readonly_static("Black",		&py_Color::Black)
		.def_readonly_static("White",		&py_Color::White)
		.def_readonly_static("Red",			&py_Color::Red)
		.def_readonly_static("Green",		&py_Color::Green)
		.def_readonly_static("Blue",		&py_Color::Blue)
		.def_readonly_static("Yellow",		&py_Color::Yellow)
		.def_readonly_static("Magenta",		&py_Color::Magenta)
		.def_readonly_static("Cyan",		&py_Color::Cyan)
		.def_readonly_static("Transparent", &py_Color::Transparent)

		.def("__str__", &py_Color::py_str)
		.def("__repr__", &py_Color::py_str)
		.def("__eq__", &py_Color::operator==)

		.def("__add__", &py_Color::operator+)
		.def("__sub__", &py_Color::operator-)
		.def("__mul__", &py_Color::operator*)

		.def("__iadd__", &py_Color::operator+=)
		.def("__isub__", &py_Color::operator-=)
		.def("__imul__", &py_Color::operator*=)

		;
}
