#pragma once

#include <pybind11/embed.h>
#include <pybind11/stl.h>
namespace py = pybind11;

void register_color(py::module& m);
void register_draw_transform(py::module& m);
void register_event(py::module& m);
void register_rect(py::module& m);
void register_shape(py::module& m);
void register_vect(py::module& m);
void register_vecti(py::module& m);
