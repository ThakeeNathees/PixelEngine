#pragma once

#include <pybind11/embed.h>
namespace py = pybind11;

struct py_Color : public sf::Color
{
	py_Color() : sf::Color() {}
	py_Color(int r, int g, int b, int a = 255) : sf::Color(r, g, b, a) {}

};

void register_color(py::module m)
{

}