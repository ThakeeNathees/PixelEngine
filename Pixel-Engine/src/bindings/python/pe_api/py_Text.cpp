#include "pch.h"
#include "pe_api.h"

#include "api/misc/Text.h"

void register_text(py::module& m)
{

	py::class_<pe::Text, sf::Drawable, sf::Transformable>py_text(m, "Text");

	py::enum_ <pe::Text::Style>(py_text, "Style")
		.value("BOLD", pe::Text::Style::Bold)
		.value("ITALIC", pe::Text::Style::Italic)
		.value("REGULAR", pe::Text::Style::Regular)
		.value("STRIKETHROUGH", pe::Text::Style::StrikeThrough)
		.value("UNDERLINED", pe::Text::Style::Underlined)
		.export_values()
		;

	py_text
		.def(py::init<>())
		.def(py::init<const std::string&, const pe::Font&, unsigned int>())
		.def(py::init<const std::string&, unsigned int>())
		.def("setFont", [](pe::Text& self, pe::Font* font) {self.setFont(font); })
		.def("setCharacterSize", &pe::Text::setCharacterSize)
		.def("setLineSpacing", &pe::Text::setLineSpacing)
		.def("setLetterSpacing", &pe::Text::setLetterSpacing)
		.def("setFillColor", &pe::Text::setFillColor)
		.def("setOutlineColor", &pe::Text::setOutlineColor)
		.def("setOutlineThickness", &pe::Text::setOutlineThickness)
		.def("setStyle", [](pe::Text& self, int style) { self.setStyle(style); })

		.def("setStyle", [](pe::Text& self)->int { return static_cast<int>(self.getStyle()); })
		//.def("getString", [](pe::Text& self)->const std::string&  { return self.getString(); }) //TODO: create sf::String
		.def("setString", [](pe::Text& self, const std::string& str) { self.setString(str); })
		.def("getFont", [](pe::Text& self)
			{
				return self.getFont();
			}, py::return_value_policy::reference)

		.def("getCharacterSize",&pe::Text::getCharacterSize)
		.def("getLetterSpacing",&pe::Text::getLetterSpacing)
		.def("getLineSpacing",&pe::Text::getLineSpacing)
		.def("getFillColor",&pe::Text::getFillColor)
		.def("getOutlineColor",&pe::Text::getOutlineColor)
		.def("getOutlineThickness",&pe::Text::getOutlineThickness)
		.def("findCharacterPos",&pe::Text::findCharacterPos)
		.def("getLocalBounds",&pe::Text::getLocalBounds)
		.def("getGlobalBounds",&pe::Text::getGlobalBounds)
		;

	// todo: set style text
}

