#pragma once
#include "api/core.h"

#include <pybind11/embed.h>
namespace py = pybind11;

#include "types/py_Vect.h"
#include "types/py_Color.h"
#include "types/py_Rect.h"
#include "types/py_Draw_Trans.h"
#include "types/py_sf_Texture.h"
#include "types/py_Shape.h"

#include "entities/py_Texture.h"
/*
#include "entities/py_Sprite.h"
*/

//#include "api/entities/Asset.h"

// import pixel_engine as pe
PYBIND11_EMBEDDED_MODULE(pixel_engine, m) { 

	py::class_<pe::Asset>(m, "Asset")
		.def("getId", &pe::Asset::getId)
		;

	py::enum_<pe::Asset::Type>(m, "AssetTypes")
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
	register_sf_texture(m);
	register_shape(m);

	// entities
	register_texture(m);

	/*

	register_sprite(m);
	*/
}
