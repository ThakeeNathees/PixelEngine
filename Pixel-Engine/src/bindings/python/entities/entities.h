#pragma once

#include <pybind11/embed.h>
#include <pybind11/stl.h>
namespace py = pybind11;

void register_animation(py::module& m);
void register_area(py::module& m);
void register_object(py::module m);
void register_signal_timer(py::module& m);
void register_sprite(py::module& m);
void register_texture(py::module& m);
void register_bg(py::module& m);