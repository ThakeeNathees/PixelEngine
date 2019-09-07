#pragma once

#include <pybind11/embed.h>
namespace py = pybind11;

#include "SFML/Graphics.hpp"

void register_sf_texture(py::module m)
{
	py::class_<sf::Texture>(m,"_Texture")
		.def("create", &sf::Texture::create)
		.def("loadFromFile", [](sf::Texture& self, const py::str& file_name, const sf::IntRect& area) 
			{
				self.loadFromFile(file_name.cast<std::string>(), area );
			}
			, py::arg("file_name"), py::arg("area") = sf::IntRect()
		)
		.def("getSize", [](const sf::Texture& self) -> sf::Vector2i
			{
				return static_cast<sf::Vector2i>(self.getSize());
			}
		)
		
		.def("setSmooth", &sf::Texture::setSmooth)
		.def("isSmooth", &sf::Texture::isSmooth)
		.def("setSrgb", &sf::Texture::setSrgb)
		.def("isSrgb", &sf::Texture::isSrgb)
		.def("setRepeated", &sf::Texture::setRepeated)
		.def("isRepeated", &sf::Texture::isRepeated)

		
		
		// TODO: load from memory, stream, image, copy to image, update, generate mipmap and everything after that
		;
}