#include "pch.h"
#include "pe_api.h"

#include "api/misc/Font.h"

void register_font(py::module& m)
{
	py::class_<pe::Font, pe::Asset>py_font(m, "Font");
	py::class_<pe::Font::Info>(py_font, "Info")
		.def_readonly("family", &pe::Font::Info::family)
		;

	py_font
		.def(py::init<>())
		.def(py::init<const std::string&>())

		.def("loadFromFile", &pe::Font::loadFromFile)
		.def("getInfo", &pe::Font::getInfo, py::return_value_policy::reference)
		.def("getLineSpacing", &pe::Font::getLineSpacing)
		.def("getUnderlinePosition", &pe::Font::getUnderlinePosition)
		.def("getUnderlineThickness", &pe::Font::getUnderlineThickness)
		//.def("getTexture", &pe::Font::getTexture) // todo: sf::Texture
		;
}