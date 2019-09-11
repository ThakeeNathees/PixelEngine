#include "pch.h"
#include "types.h"

#include <pybind11/embed.h>
namespace py = pybind11;

#include "api/Application.h"

void register_shape(py::module& m)
{
	py::class_<sf::Shape, sf::Drawable, sf::Transformable>(m, "Shape")

		.def("setTexture", [](sf::Shape& self, pe::Texture* texture, bool resetrect) {self.setTexture(texture, resetrect); }, py::arg("texture"), py::arg("resetrect") = false)
		.def("setTextureRect", [](sf::Shape& self, const sf::IntRect& rect) {self.setTextureRect(rect); })
		.def("setFillColor", [](sf::Shape& self, const sf::Color& color) {self.setFillColor(color); })
		.def("setOutlineColor", [](sf::Shape& self, const sf::Color& color) {self.setOutlineColor(color); })
		.def("setOutlineThickness", [](sf::Shape& self, float thickness) {self.setOutlineThickness(thickness); })

		.def("getTexture", [](sf::Shape& self) { return static_cast<const pe::Texture*>(self.getTexture()); }, py::return_value_policy::reference)
		.def("getTextureRect", [](sf::Shape& self) {return self.getTextureRect(); })
		.def("getFillColor", [](sf::Shape& self) {return self.getFillColor(); })
		.def("getOutlineColor", [](sf::Shape& self) {return self.getOutlineColor(); })
		.def("getOutlineThickness", [](sf::Shape& self) {return self.getOutlineThickness(); })

		.def("getPointCount", [](sf::Shape& self) {return self.getPointCount(); })
		.def("getPoint", [](sf::Shape& self, int index) {return self.getPoint(index); })
		.def("getLocalBounds", [](sf::Shape& self) { return self.getLocalBounds(); })
		.def("getGlobalBounds", [](sf::Shape& self) {return self.getGlobalBounds(); })
		;

	py::class_<sf::ConvexShape, sf::Shape>(m, "ConvexShape")
		.def(py::init<std::size_t>(), py::arg("point_count") = 0)
		.def("setPointCount", [](sf::ConvexShape& self, int count) {self.setPointCount(count); })
		.def("setPoint", [](sf::ConvexShape& self, int index, const sf::Vector2f& point) {self.setPoint(index, point); })
		;
	py::class_<sf::RectangleShape, sf::Shape>(m, "RectangleShape")
		.def(py::init<const sf::Vector2f&>(), py::arg("size")=sf::Vector2f(0,0))
		.def("setSize", [](sf::RectangleShape& self, const sf::Vector2f& size) {return self.setSize(size); })
		.def("getSize", [](sf::RectangleShape& self) {return self.getSize(); })
		;
	py::class_<sf::CircleShape, sf::Shape>(m, "CircleShape")
		.def(py::init<float, std::size_t>(), py::arg("radius") = 0, py::arg("point_count") = 30)
		.def("setRadius", [](sf::CircleShape& self, float r) {self.setRadius(r); })
		.def("getRadius", [](sf::CircleShape& self) {return self.getRadius(); })
		.def("setPointCount", [](sf::CircleShape& self, int point_count) {self.setPointCount(point_count); })
		.def("getPointCount", [](sf::CircleShape& self) {return self.getPointCount(); })
		;
}
