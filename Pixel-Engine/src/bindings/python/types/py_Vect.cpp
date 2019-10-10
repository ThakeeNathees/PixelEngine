#include "pch.h"
#include "types.h"

#include <pybind11/embed.h>
namespace py = pybind11;


void register_vect(py::module& m) 
{
	py::class_<sf::Vector2f>(m, "Vect")
		.def(py::init<>())
		.def(py::init<float, float>())
		.def_readwrite("x", &sf::Vector2f::x)
		.def_readwrite("y", &sf::Vector2f::y)

		.def("__str__", [](py::object o)->py::str 
			{
				py::str _ret; 
				_ret = std::string("(").append(std::to_string(o.attr("x").cast<float>())).append(", ").append(std::to_string(o.attr("y").cast<float>())).append(" )");
				return _ret;
			}
		)
		.def("__add__", [](const sf::Vector2f& self, const sf::Vector2f& other) { return self + other; })
		.def("__sub__", [](const sf::Vector2f& self, const sf::Vector2f& other) { return self - other; })
		.def("__mul__", [](const sf::Vector2f& self, const sf::Vector2f& other)
			{
				sf::Vector2f _ret;
				_ret.x = self.x * other.x;
				_ret.y = self.y * other.y;
				return _ret;
			}
		)
		.def("__mul__", [](const sf::Vector2f& self, float val) -> sf::Vector2f {
				sf::Vector2f _ret;
				_ret.x = self.x * val;
				_ret.y = self.y * val;
				return _ret;
			}
		)
		.def("__rmul__", [](const sf::Vector2f& self, float val) -> sf::Vector2f {
				sf::Vector2f _ret;
				_ret.x = self.x * val;
				_ret.y = self.y * val;
				return _ret;
			}
		)
		.def("__truediv__", [](const sf::Vector2f& self, float val) -> sf::Vector2f {
				sf::Vector2f _ret;
				_ret.x = self.x / val;
				_ret.y = self.y / val;
				return _ret;
			}
		)
		.def("__eq__",   [](const sf::Vector2f& self, const sf::Vector2f& other) -> bool { return self == other; })
		;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// TODO: depricate vect2i for python users
void register_vecti(py::module& m)
{
	py::class_<sf::Vector2i>(m, "Vecti")
		.def(py::init<>())
		.def(py::init<float, float>())
		.def_readwrite("x", &sf::Vector2i::x)
		.def_readwrite("y", &sf::Vector2i::y)

		.def("__str__", [](py::object o)->py::str
			{
				py::str _ret;
				_ret = std::string("(").append(std::to_string(o.attr("x").cast<float>())).append(", ").append(std::to_string(o.attr("y").cast<float>())).append(" )");
				return _ret;
			}
		)
		.def("__add__", [](const sf::Vector2i& self, const sf::Vector2i& other) { return self + other; })
		.def("__sub__", [](const sf::Vector2i& self, const sf::Vector2i& other) { return self - other; })
		.def("__mul__", [](const sf::Vector2i& self, const sf::Vector2i& other)
			{
				sf::Vector2i _ret;
				_ret.x = self.x * other.x;
				_ret.y = self.y * other.y;
				return _ret;
			}
		)
		.def("__mul__", [](const sf::Vector2i& self, float val) -> sf::Vector2i {
				sf::Vector2i _ret;
				_ret.x = static_cast<int>(self.x * val);
				_ret.y = static_cast<int>(self.y * val);
				return _ret;
			}
		)
		.def("__rmul__", [](const sf::Vector2i& self, float val) -> sf::Vector2i {
		sf::Vector2i _ret;
		_ret.x = static_cast<int>(self.x * val);
		_ret.y = static_cast<int>(self.y * val);
		return _ret;
			}
		)
		.def("__truediv__", [](const sf::Vector2i& self, float val) -> sf::Vector2i {
				sf::Vector2i _ret;
				_ret.x = static_cast<int>(self.x / val);
				_ret.y = static_cast<int>(self.y / val);
				return _ret;
			}
		)
		.def("__eq__", [](const sf::Vector2i& self, const sf::Vector2i& other) -> bool { return self == other; })
		;
}