#pragma once
#include "api/core.h"


#include <pybind11/embed.h>
namespace py = pybind11;

#include "types/py_Vect.h"
#include "types/py_Color.h"
#include "types/py_Rect.h"
#include "types/py_Shape.h"
#include "types/py_Color.h"

#include "entities/py_Texture.h"
#include "entities/py_Sprite.h"

// import pixel_engine as pe
PYBIND11_EMBEDDED_MODULE(pixel_engine, m) { 
	register_vect(m);
	register_color(m);
	register_rect(m);
	register_shape(m);

	py::enum_<pe::Asset::Type>(m, "Asset")
		.value("Texture",		pe::Asset::Type::Texture)
		.value("Font",			pe::Asset::Type::Font)
		.value("Area",			pe::Asset::Type::Area)
		.value("Sprite",		pe::Asset::Type::Sprite)
		.value("Background",	pe::Asset::Type::Background)
		.value("Animation",		pe::Asset::Type::Animation)
		.value("Object",		pe::Asset::Type::Object)
		.value("Scene",			pe::Asset::Type::Scene)
	;

	register_texture(m);
	register_sprite(m);
}
