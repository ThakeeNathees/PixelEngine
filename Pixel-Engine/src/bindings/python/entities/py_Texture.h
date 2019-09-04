#pragma once

#include <pybind11/embed.h>
namespace py = pybind11;

#include "../types/py_Rect.h"

class py_Texture : public pe::Texture
{
public:
	py_Texture() : pe::Texture() {}
	py_Texture(const pe::Texture& texture) : pe::Texture(texture) {}
	bool py_loadFromFile(const py::str& file_name, const py_Rect& area) { return sf::Texture::loadFromFile( file_name.cast<std::string>(), area.asSfIntRect() ); }
	bool py_loadFromFile(const py::str& file_name) { return sf::Texture::loadFromFile( file_name.cast<std::string>() ); }
	py_Vect py_getSize() {  return py_Vect(sf::Texture::getSize().x, sf::Texture::getSize().y); }

	void py_setName(const py::str name) { pe::Texture::setName(name.cast<std::string>()); }
	const py::str& py_getName() { return pe::Texture::getName(); }
	const py::str& py_getPath() { return pe::Texture::getPath(); }
};

void register_texture(py::module m)
{

	py::class_<py_Texture>(m, "Texture")
		.def(py::init<>())
		.def("create",			&py_Texture::create)
		.def("loadFromFile",	(bool (py_Texture::*)(const py::str&, const py_Rect&)) &::py_Texture::py_loadFromFile)
		.def("loadFromFile",	(bool (py_Texture::*)(const py::str&)) &::py_Texture::py_loadFromFile)
		.def("getSize",			&py_Texture::py_getSize)
		.def("setSmooth",		&py_Texture::setSmooth)
		.def("isSmooth",		&py_Texture::isSmooth)
		.def("setSrgb",			&py_Texture::setSrgb)
		.def("isSrgb",			&py_Texture::isSrgb)
		.def("setRepeated",		&py_Texture::setRepeated)
		.def("isRepeated",		&py_Texture::isRepeated)
		.def("generateMipmap",	&py_Texture::generateMipmap)
		.def("setName",			&py_Texture::py_setName)
		.def("getName",			&py_Texture::py_getName)
		.def("getPath",			&py_Texture::py_getPath)
		.def_static("getCount", &py_Texture::getCount)
		// TODO: define the rest

		;
}