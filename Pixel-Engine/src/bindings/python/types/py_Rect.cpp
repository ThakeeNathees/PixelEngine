#include "pch.h"
#include "types.h"

#include <pybind11/embed.h>
namespace py = pybind11;


void register_rect(py::module& m)
{
	py::class_<sf::FloatRect>(m, "Rect")
		.def(py::init<>())
		.def(py::init<float, float, float, float>())
		.def(py::init<const sf::Vector2f&, const sf::Vector2f&>())

		.def_readwrite("x", &sf::FloatRect::left)
		.def_readwrite("y", &sf::FloatRect::top)
		.def_readwrite("w", &sf::FloatRect::width)
		.def_readwrite("h", &sf::FloatRect::height)
		
		.def("isContain", [](sf::FloatRect& self, float x, float y) {return self.contains(x, y); })
		.def("isContain", [](sf::FloatRect& self, const sf::Vector2f& point) {return self.contains(point); })
		.def("isIntersects", [](sf::FloatRect& self, const sf::FloatRect& other) { return self.intersects(other); })

		.def("__eq__", [](const sf::FloatRect& self, const sf::FloatRect& other) { return self == other; })

		;

	///////////////////////////////////////

	py::class_<sf::IntRect>(m, "Recti")
		.def(py::init<>())
		.def(py::init<int, int, int, int>())
		.def(py::init<const sf::Vector2i&, const sf::Vector2i&>())

		.def_readwrite("x", &sf::IntRect::left)
		.def_readwrite("y", &sf::IntRect::top)
		.def_readwrite("w", &sf::IntRect::width)
		.def_readwrite("h", &sf::IntRect::height)

		.def("isContain", [](sf::IntRect& self, int x, int y) {return self.contains(x, y); })
		.def("isContain", [](sf::IntRect& self, const sf::Vector2i& point) {return self.contains(point); })
		.def("isIntersects", [](sf::IntRect& self, const sf::IntRect& other) { return self.intersects(other); })

		.def("__eq__", [](const sf::IntRect& self, const sf::IntRect& other) { return self == other; })

		;
}