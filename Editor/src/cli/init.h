#pragma once

#include <pybind11/embed.h>
namespace py = pybind11;

#include "../path_handler/PathHandler.h"

int cliInit(int argc, char** argv) {
	if (argc < 3) {
		// print error
		return 1;
	}

	auto str_util = py::module::import("str_util");
	int error = str_util.attr("is_valid_proj_name")(argv[2]).cast<int>();
	if (error) {
		return 2;
	}
	auto init = py::module::import("init");
	init.attr("init")(argv[2]);
	auto os = py::module::import("os");
	PathHandler::chDir(os.attr("path").attr("join")(os.attr("getcwd")(), argv[2]).cast<std::string>());
	return 0;
}
