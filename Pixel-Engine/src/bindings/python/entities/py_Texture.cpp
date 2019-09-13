#include "pch.h"
#include "entities.h"

#include <pybind11/embed.h>
namespace py = pybind11;

#include "api/misc/Texture.h"
#include "api/Assets.h"

void register_texture(py::module& m)
{

	py::class_<pe::Texture, pe::Asset>(m, "Texture")
		.def(py::init<>())
		.def(py::init<py::str>())
		.def_static("new", []() { return pe::Assets::newAsset<pe::Texture>(); }, py::return_value_policy::reference)
		.def_static("new", [](const std::string& name) { return pe::Assets::newAsset<pe::Texture>(name); }, py::return_value_policy::reference)
		.def_static("getCount", pe::Texture::getCount)

		// methods
		.def("loadFromFile", [](pe::Texture& self, const std::string& path, const sf::IntRect& rect) {self.loadFromFile(path, rect); }, py::arg("path"), py::arg("area") = sf::IntRect())

		.def("create", [](pe::Texture& self, int w, int h) {self.create(w, h); })
		.def("getSize", [](const sf::Texture& self) -> sf::Vector2i
			{
				return static_cast<sf::Vector2i>(self.getSize());
			}
		)

		.def("setSmooth", [](pe::Texture& self, bool smooth) {self.setSmooth(smooth); })
		.def("isSmooth", [](pe::Texture& self) {return self.isSmooth(); })
		.def("setSrgb", [](pe::Texture& self, bool srgb) {self.setSrgb(srgb); })
		.def("isSrgb", [](pe::Texture& self) {return self.isSrgb(); })
		.def("setRepeated", [](pe::Texture& self, bool rep) {self.setRepeated(rep); })
		.def("isRepeated", [](pe::Texture& self) {return self.isRepeated(); })



		// TODO: load from memory, stream, image, copy to image, update, generate mipmap and everything after that
		;
}