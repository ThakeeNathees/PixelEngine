#include "pch.h"
#include "entities.h"

#include <pybind11/embed.h>
namespace py = pybind11;

#include "api/entities/Sprite.h"
#include "api/Assets.h"

void register_sprite(py::module& m)
{
	py::class_<pe::Sprite, sf::Drawable, sf::Transformable, pe::Asset >(m, "Sprite")
		.def(py::init<>())
		.def(py::init<py::str>())
		.def_static("new", []() { return pe::Assets::newAsset<pe::Sprite>(); }, py::return_value_policy::reference)
		.def_static("new", [](const std::string& name) { return pe::Assets::newAsset<pe::Sprite>(name); }, py::return_value_policy::reference)
		.def_static("getCount", []() {return pe::Sprite::getCount(); })


		// methods
		.def("setTexture", [](pe::Sprite& self, pe::Texture& tex, bool reset_rect) {self.setTexture(tex, reset_rect); }, py::arg("texture"), py::arg("reset_rect") = false)
		.def("setFrames", [](pe::Sprite& self, int x, int y, int off_x, int off_y) {self.setFrames(x, y, off_x, off_y); }, py::arg("x"), py::arg("y"), py::arg("offset_x") = 0, py::arg("offset_y") = 0)
		.def("setFrames", [](pe::Sprite& self, std::tuple<sf::Vector2i, sf::Vector2i> tup) 
			{
				self.setFrames( std::get<0>(tup).x, std::get<0>(tup).y, std::get<1>(tup).x, std::get<1>(tup).y );
			}
		)
		.def("setFrameIndex", [](pe::Sprite& self, int ind) {self.setFrameIndex(ind); })
		.def("getFrames", [](pe::Sprite& self) {return self.getFrames(); })
		.def("getFrameCount", [](pe::Sprite& self) {return self.getFrameCount(); })
		.def("getFrameIndex", [](pe::Sprite& self) {return self.getFrameIndex(); })
		.def("getTexture", [](pe::Sprite& self) ->pe::Texture* {
				if (!self.hasTexture()) return nullptr;
				return &self.getTexture();
			}
			, py::return_value_policy::reference
		)
		;
}