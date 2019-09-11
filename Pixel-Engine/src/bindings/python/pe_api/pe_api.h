#pragma once

#include <pybind11/embed.h>
namespace py = pybind11;

void register_assets(py::module& m);
