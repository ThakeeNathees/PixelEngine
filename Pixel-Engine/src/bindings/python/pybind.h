#pragma once
#include "api/core.h"

#include <pybind11/stl.h>
#include <pybind11/embed.h>
namespace py = pybind11;

#include "types/py_Vect.h"
#include "types/py_Color.h"
#include "types/py_Rect.h"
#include "types/py_Draw_Trans.h"
#include "types/py_Shape.h"

#include "types/py_Event.h"

#include "entities/py_Texture.h"
#include "entities/py_Sprite.h"
#include "entities/py_Area.h"
#include "entities/py_Signal_Timer.h"
#include "entities/py_Animation.h"

// import pixel_engine as pe
PYBIND11_EMBEDDED_MODULE(pixel_engine, m) { 

	py::class_<pe::Asset> py_asset(m, "Asset");
	py_asset
		.def("getId", &pe::Asset::getId)
		.def("getName", &pe::Asset::getName)
		.def("setName", &pe::Asset::setName)
		.def("getType", &pe::Asset::getType)
	;

	py::enum_<pe::Asset::Type>(py_asset, "AssetTypes")
		.value("Texture",		pe::Asset::Type::Texture)
		.value("Font",			pe::Asset::Type::Font)
		.value("Area",			pe::Asset::Type::Area)
		.value("Sprite",		pe::Asset::Type::Sprite)
		.value("Background",	pe::Asset::Type::Background)
		.value("Animation",		pe::Asset::Type::Animation)
		.value("Object",		pe::Asset::Type::Object)
		.value("Scene",			pe::Asset::Type::Scene)
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
	register_area(m);
	register_signal_timer(m);
	register_animation(m);

}
