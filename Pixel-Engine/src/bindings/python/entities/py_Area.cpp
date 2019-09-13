#include "pch.h"
#include "entities.h"

#include <pybind11/embed.h>
namespace py = pybind11;

#include "api/entities/Area.h"
#include "api/Assets.h"

void register_area(py::module& m)
{
	py::class_<pe::Area, sf::Transformable, pe::Asset>(m, "Area")
		.def(py::init<>())
		.def(py::init<py::str>())
		.def_static("new", []() { return pe::Assets::newAsset<pe::Area>(); }, py::return_value_policy::reference)
		.def_static("new", [](const std::string& name) { return pe::Assets::newAsset<pe::Area>(name); }, py::return_value_policy::reference)
		.def_static("getCount", &pe::Area::getCount)

		.def("getCentroid", [](pe::Area& self, bool local) {return self.getCentroid(local); }, py::arg("local") = false)
		.def("isContains", [](pe::Area& self, float x, float y) {return self.isContains(x, y); })
		.def("isContains", [](pe::Area& self, const sf::Vector2f& point) {return self.isContains(point); })
		.def("isConvex", [](pe::Area& self) {return self.isConvex(); })
		.def("isIntersecting", [](pe::Area& self, const pe::Area& other) {return self.isIntersecting(other); })
		.def("setShape", [](pe::Area& self, sf::Shape* shape) { self.setShape(shape); })
		.def("getShape", [](const pe::Area& self) -> sf::Shape*
			{
				if (!self.hasShape()) return nullptr;
				return &self.getShape();
			}, py::return_value_policy::reference)

		.def("setPosition", [](pe::Area& self, float x, float y) {self.setPosition(x,y); })
		.def("setPosition", [](pe::Area& self, const sf::Vector2f& pos) {self.setPosition(pos); })
		.def("setRotation", [](pe::Area& self, float angle) {self.setRotation(angle); })
		.def("setScale", [](pe::Area& self, float x, float y) {self.setScale(x, y); })
		.def("setScale", [](pe::Area& self, const sf::Vector2f& scale) {self.setScale(scale); })
		.def("setOrigin", [](pe::Area& self, float x, float y) {self.setOrigin(x, y); })
		.def("setOrigin", [](pe::Area& self, const sf::Vector2f& origin) {self.setOrigin(origin); })

		.def("move", [](pe::Area& self, float x, float y) {self.move(x, y); })
		.def("move", [](pe::Area& self, const sf::Vector2f& dir) {self.move(dir); })
		.def("rotate", [](pe::Area& self, float angle) {self.rotate(angle); })
		.def("scale", [](pe::Area& self, float x, float y) {self.scale(x, y); })
		.def("scale", [](pe::Area& self, const sf::Vector2f& scale) {self.scale(scale); })
		;		
}
