#pragma once

#pragma once

#include "api/core.h"
#include "api/Application.h"

#include "types/types.h"
#include "entities/entities.h"
#include "pe_api/pe_api.h"

#include <pybind11/embed.h>
namespace py = pybind11;

// import pixel_engine as pe
PYBIND11_EMBEDDED_MODULE(pixel_engine, m) {

	py::class_<pe::Asset> py_asset(m, "Asset");
	py_asset
		.def("getId", [](pe::Asset& self) {return self.getId(); })
		.def("getName", [](pe::Asset& self) {return self.getName(); })
		.def("setName", [](pe::Asset& self, const std::string& name) {self.setName(name); })
		.def("getType", [](pe::Asset& self) {return self.getType(); })
		;
	

	py::enum_<pe::Asset::Type>(py_asset, "AssetTypes")
		.value("Texture", pe::Asset::Type::Texture)
		.value("Font", pe::Asset::Type::Font)
		.value("Area", pe::Asset::Type::Area)
		.value("Sprite", pe::Asset::Type::Sprite)
		.value("Background", pe::Asset::Type::Background)
		.value("Animation", pe::Asset::Type::Animation)
		.value("Object", pe::Asset::Type::Object)
		.value("Scene", pe::Asset::Type::Scene)
		;


	// types
	register_vect(m);
	register_vecti(m);
	register_color(m);
	register_rect(m);
	register_draw_transform(m);
	register_shape(m);
	register_event(m);

	// entities
	register_texture(m);
	register_sprite(m);
	register_bg(m);
	register_area(m);
	register_signal_timer(m);
	register_animation(m);
	register_object(m);	

	// pe_api
	register_assets(m);
}

