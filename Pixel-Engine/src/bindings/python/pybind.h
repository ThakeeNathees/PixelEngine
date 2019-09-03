#pragma once
#include "api/core.h"


#include <pybind11/stl.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <pybind11/chrono.h>
#include <pybind11/embed.h>
namespace py = pybind11;

#include "py_Vect.h"

// import pixel_engine as pe
PYBIND11_EMBEDDED_MODULE(pixel_engine, m) { 
	register_vect(m);

}
