#pragma once

#include <pybind11/embed.h>
#include <pybind11/stl.h>
namespace py = pybind11;

void register_assets(py::module& m);
void register_font(py::module& m);
void register_text(py::module& m);
void register_scene(py::module& m);