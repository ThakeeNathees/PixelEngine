#include "pch.h"
#include "entities.h"

#include "api/entities/Background.h"
#include "api/Assets.h"

void register_bg(py::module& m)
{
	py::class_<pe::Background, sf::Drawable, sf::Transformable, pe::Asset >(m, "Background")
		.def(py::init<>())
		.def(py::init<py::str>())
		.def_static("new", []() { return pe::Assets::newAsset<pe::Background>(); }, py::return_value_policy::reference)
		.def_static("new", [](const std::string& name) { return pe::Assets::newAsset<pe::Background>(name); }, py::return_value_policy::reference)
		.def_static("getCount", []() {return pe::Background::getCount(); })

		.def("setTexture", &pe::Background::setTexture)
		.def("setVisible", &pe::Background::setVisible)
		.def("setRepeated", &pe::Background::setRepeatd)
		.def("setSmooth", &pe::Background::setSmooth)
		.def("setMoveSpeed", (void(pe::Background::*)(int, int)) &pe::Background::setMoveSpeed)
		.def("setMoveSpeed", (void(pe::Background::*)(const sf::Vector2i& speed)) &pe::Background::setMoveSpeed)

		.def("getName", &pe::Background::getName, py::return_value_policy::reference)
		.def("isVisible", &pe::Background::isVisible)
		.def("isRepeat", &pe::Background::isRepeat)
		.def("isSmooth", &pe::Background::isSmooth)
		.def("getTexture", [](pe::Background& self) -> pe::Texture*
			{
				if (!self.hasTexture()) return nullptr;
				return &self.getTexture();
			}, py::return_value_policy::reference
		)
		.def("getMoveSpeed", &pe::Background::getMoveSpeed)
		;
}
