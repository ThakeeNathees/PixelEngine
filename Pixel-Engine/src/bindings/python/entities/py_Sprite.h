#pragma once

#include <pybind11/embed.h>
namespace py = pybind11;

#include "py_Texture.h"
/*
class py_Sprite : public pe::Sprite
{
public:
	py_Sprite() : pe::Sprite() {}
	py_Sprite(const py::str name) : pe::Sprite(name.cast<std::string>()) {}

	void py_setName(const py::str name) { pe::Sprite::setName(name.cast<std::string>()); }
	void py_setTexture(py_Texture& texture, bool reset=false) { pe::Sprite::setTexture(texture, reset); }
	const py::str& py_getName() const { return py_Sprite::getName(); }
	py::tuple py_getFrames() const { auto f = pe::Sprite::getFrames(); return py::make_tuple(py_Vect(f.x, f.y), py_Vect(f.z, f.w)); }
	py_Texture* py_getTexture() const { if (pe::Sprite::hasTexture()) return (py_Texture*)& pe::Sprite::getTexture(); else return nullptr; }

	void py_setTextureRect(const py_Rect& rect) { pe::Sprite::setTextureRect(rect.asSfIntRect()); }
	void py_setColor(const py_Color& color) { pe::Sprite::setColor(color); }
	const py_Rect& py_getTextureRect() { return pe::Sprite::getTextureRect(); }
	const py_Color& py_Color() { return pe::Sprite::getColor(); }
	const py_Rect& py_getLocalBounds() { return pe::Sprite::getLocalBounds(); }
	const py_Rect& py_getGlobalBounds() { return pe::Sprite::getGlobalBounds(); }
};
*/

void register_sprite(py::module& m)
{
	py::class_<pe::Sprite, sf::Drawable, sf::Transformable, pe::Asset >(m, "Sprite")
		.def(py::init<>())
		.def(py::init<py::str>())

		// static
		.def_static("getCount", &pe::Sprite::getCount)


		// methods
		.def("setTexture",	&pe::Sprite::setTexture, py::arg("texture"), py::arg("reset_rect")=false)
		.def("setFrames",	(void(pe::Sprite::*)(int, int, int, int))&pe::Sprite::setFrames, py::arg("x"), py::arg("y"), py::arg("offset_x")=0, py::arg("offset_y")=0)
		.def("setFrames", [](pe::Sprite& self, std::tuple<sf::Vector2i, sf::Vector2i> tup) 
			{
				self.setFrames( std::get<0>(tup).x, std::get<0>(tup).y, std::get<1>(tup).x, std::get<1>(tup).y );
			}
		)
		.def("setFrameIndex", &pe::Sprite::setFrameIndex)
		.def("getFrames", &pe::Sprite::getFrames)
		.def("getFrameCount",&pe::Sprite::getFrameCount)
		.def("getFrameIndex", &pe::Sprite::getFrameIndex)
		.def("getTexture", [](pe::Sprite& self) ->pe::Texture* {
				if (!self.hasTexture()) return nullptr;
				return &self.getTexture();
			}
		)
		;
}