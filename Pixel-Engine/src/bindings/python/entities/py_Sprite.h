#pragma once

#include <pybind11/embed.h>
namespace py = pybind11;

#include "py_Texture.h"

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

void register_sprite(py::module m)
{
	py::class_<py_Sprite>(m, "Sprite")
		.def(py::init<>())
		.def(py::init<py::str>())
		.def("setFrames", (void (py_Sprite::*)(int, int, int, int)) &py_Sprite::setFrames)
		.def("setName", &py_Sprite::py_setName)
		.def("setTexture", &py_Sprite::py_setTexture, py::arg("texture"), py::arg("reset")=false)
		.def("setFrameIndex", &py_Sprite::setFrameIndex)

		.def("getName", &py_Sprite::py_getName)
		.def("getId", &py_Sprite::getId)
		.def("getType", &py_Sprite::getType)
		.def("getFrames", &py_Sprite::py_getFrames)
		.def("getFrameIndex", &py_Sprite::getFrameIndex)
		.def("getTexture", &py_Sprite::py_getTexture)
		.def("hasTexture", &py_Sprite::hasTexture)
		.def("getTextureRect", &py_Sprite::py_getTextureRect)
		.def("getLocalBounds", &py_Sprite::py_getLocalBounds)
		.def("getGlobalBounds", &py_Sprite::py_getGlobalBounds)
		;
}