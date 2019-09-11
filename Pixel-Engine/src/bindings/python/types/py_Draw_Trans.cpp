#include "pch.h"
#include "types.h"

#include <pybind11/embed.h>
namespace py = pybind11;

#include "api/misc/Drawable.h"

void register_draw_transform(py::module& m)
{
	py::class_<sf::Drawable>(m, "__sfDrawable");
	
	py::class_<pe::Drawable>(m, "__peDrawable")
		.def("getZindex", [](pe::Drawable& self) {return self.getZindex(); })
		.def("setZindex", [](pe::Drawable& self, int z_index) {return self.setZindex(z_index); })
		.def("isVisible", [](pe::Drawable& self) {return self.isVisible(); })
		.def("setVisible", [](pe::Drawable& self, bool visible) {return self.setVisible(visible); })
		;

	py::class_<sf::Transformable>(m, "Transformable")

		.def(py::init<>())
		.def("setPosition", [](sf::Transformable& self, float x, float y) { self.setPosition(x, y); })
		.def("setPosition", [](sf::Transformable& self, const sf::Vector2f& position) {self.setPosition(position); })
		.def("setRotation", [](sf::Transformable& self, float angle) {self.setRotation(angle); })
		.def("setScale", [](sf::Transformable& self, float x, float y) {self.setScale(x, y); })
		.def("setScale", [](sf::Transformable& self,const sf::Vector2f& scale) {self.setScale(scale); })
		.def("setOrigin", [](sf::Transformable& self, float x, float y) {self.setOrigin(x, y); })
		.def("setOrigin", [](sf::Transformable& self, const sf::Vector2f& origin) {self.setOrigin(origin); })

		.def("getPosition", [](sf::Transformable& self) {return self.getPosition(); })
		.def("getRotation", [](sf::Transformable& self) {return self.getRotation(); })
		.def("getScale", [](sf::Transformable& self) {return self.getScale(); })
		.def("getOrigin", [](sf::Transformable& self) {return self.getOrigin(); })

		.def("move", [](sf::Transformable& self, float x, float y) {self.move(x, y); })
		.def("move", [](sf::Transformable& self, const sf::Vector2f& dir) {self.move(dir); })
		.def("rotate", [](sf::Transformable& self, float angle) {self.rotate(angle); })
		.def("scale", [](sf::Transformable& self, float x, float y) {self.scale(x,y); })
		.def("scale", [](sf::Transformable& self, const sf::Vector2f& scale) {self.scale(scale); })

		// TODO: getTransform, getinverseTransform
		;
}