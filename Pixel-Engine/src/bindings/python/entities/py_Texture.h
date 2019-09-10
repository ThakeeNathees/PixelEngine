#pragma once

#include <pybind11/embed.h>
namespace py = pybind11;

void register_texture(py::module& m)
{

	py::class_<pe::Texture, pe::Asset>(m, "Texture")
		.def(py::init<>())
		.def(py::init<py::str>())
		// satic
		.def_static("getCount", pe::Texture::getCount)

		// methods
		.def("loadFromFile", &pe::Texture::loadFromFile, py::arg("texture"), py::arg("area")=sf::IntRect())

		.def("create", &pe::Texture::create)
		.def("getSize", [](const sf::Texture& self) -> sf::Vector2i
			{
				return static_cast<sf::Vector2i>(self.getSize());
			}
		)

		.def("setSmooth",	&pe::Texture::setSmooth)
		.def("isSmooth",	&pe::Texture::isSmooth)
		.def("setSrgb",		&pe::Texture::setSrgb)
		.def("isSrgb",		&pe::Texture::isSrgb)
		.def("setRepeated", &pe::Texture::setRepeated)
		.def("isRepeated",	&pe::Texture::isRepeated)



				// TODO: load from memory, stream, image, copy to image, update, generate mipmap and everything after that
		;
}