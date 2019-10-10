#include "pch.h"
#include "pe_api.h"

#include  "api/Assets.h"

void register_assets(py::module& m)
{
	py::class_<pe::Assets>(m, "Assets")
		.def(py::init<>())
		.def_static("newTexture", []() {return pe::Assets::newAsset<pe::Texture>(); }, py::return_value_policy::reference)
		.def_static("newTexture", [](const std::string& name) {return pe::Assets::newAsset<pe::Texture>(name); }, py::return_value_policy::reference)
		.def_static("getTexture", [](int id) {return pe::Assets::getAsset<pe::Texture>(id); }, py::return_value_policy::reference)
		.def_static("getTexture", [](const std::string& name) {return pe::Assets::getAsset<pe::Texture>(name); }, py::return_value_policy::reference)

		.def_static("newFont", []() {return pe::Assets::newAsset<pe::Font>(); }, py::return_value_policy::reference)
		.def_static("newFont", [](const std::string& name) {return pe::Assets::newAsset<pe::Font>(name); }, py::return_value_policy::reference)
		.def_static("getFont", [](int id) {return pe::Assets::getAsset<pe::Font>(id); }, py::return_value_policy::reference)
		.def_static("getFont", [](const std::string& name) {return pe::Assets::getAsset<pe::Font>(name); }, py::return_value_policy::reference)

		.def_static("newArea", []() {return pe::Assets::newAsset<pe::Area>(); }, py::return_value_policy::reference)
		.def_static("newArea", [](const std::string& name) {return pe::Assets::newAsset<pe::Area>(name); }, py::return_value_policy::reference)
		.def_static("getArea", [](int id) {return pe::Assets::getAsset<pe::Area>(id); }, py::return_value_policy::reference)
		.def_static("getArea", [](const std::string& name) {return pe::Assets::getAsset<pe::Area>(name); }, py::return_value_policy::reference)

		.def_static("newSprite", []() {return pe::Assets::newAsset<pe::Sprite>(); }, py::return_value_policy::reference)
		.def_static("newSprite", [](const std::string& name) {return pe::Assets::newAsset<pe::Sprite>(name); }, py::return_value_policy::reference)
		.def_static("getSprite", [](int id) {return pe::Assets::getAsset<pe::Sprite>(id); }, py::return_value_policy::reference)
		.def_static("getSprite", [](const std::string& name) {return pe::Assets::getAsset<pe::Sprite>(name); }, py::return_value_policy::reference)

		.def_static("newBackground", []() {return pe::Assets::newAsset<pe::Background>(); }, py::return_value_policy::reference)
		.def_static("newBackground", [](const std::string& name) {return pe::Assets::newAsset<pe::Background>(name); }, py::return_value_policy::reference)
		.def_static("getBackground", [](int id) {return pe::Assets::getAsset<pe::Background>(id); }, py::return_value_policy::reference)
		.def_static("getBackground", [](const std::string& name) {return pe::Assets::getAsset<pe::Background>(name); }, py::return_value_policy::reference)

		.def_static("newAnimation", []() {return pe::Assets::newAsset<pe::Animation>(); }, py::return_value_policy::reference)
		.def_static("newAnimation", [](const std::string& name) {return pe::Assets::newAsset<pe::Animation>(name); }, py::return_value_policy::reference)
		.def_static("getAnimation", [](int id) {return pe::Assets::getAsset<pe::Animation>(id); }, py::return_value_policy::reference)
		.def_static("getAnimation", [](const std::string& name) {return pe::Assets::getAsset<pe::Animation>(name); }, py::return_value_policy::reference)

		// runtime objects nomore
		//.def_static("Object", []() {return pe::Assets::newAsset<pe::Object>(); }, py::return_value_policy::reference) 
		.def_static("getObject", [](int id) {return pe::Assets::getAsset<pe::Object>(id); }, py::return_value_policy::reference)
		.def_static("getObject", [](const std::string& name) {return pe::Assets::getAsset<pe::Object>(name); }, py::return_value_policy::reference)

		.def_static("newScene", []() {return pe::Assets::newAsset<pe::Scene>(); }, py::return_value_policy::reference)
		.def_static("newScene", [](const std::string& name) {return pe::Assets::newAsset<pe::Scene>(name); }, py::return_value_policy::reference)
		.def_static("getScene", [](int id) {return pe::Assets::getAsset<pe::Scene>(id); }, py::return_value_policy::reference)
		.def_static("getScene", [](const std::string& name) {return pe::Assets::getAsset<pe::Scene>(name); }, py::return_value_policy::reference)


		.def_static("addAssert", (void (*)(pe::Asset*)) & pe::Assets::addAsset)
		//.def("addAssert", (void (pe::Assets::*)(int id)) & pe::Assets::addAsset)
		//.def("removeAsset", &pe::Assets::removeAsset)

		.def_static("hasAsset", [](const std::string& name) {return pe::Assets::hasAsset(name); })
		.def_static("hasAsset", [](int id) {return pe::Assets::hasAsset(id); })
		;

}



