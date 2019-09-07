#pragma once

#include <pybind11/embed.h>
namespace py = pybind11;

void register_texture(py::module m)
{

	py::class_<pe::Texture, sf::Texture, pe::Asset>(m, "Texture")
		.def(py::init<>())
		.def(py::init<py::str>())

		// TODO: define the rest

		;
}