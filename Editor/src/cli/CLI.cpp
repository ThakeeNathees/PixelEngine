#include "pch.h"
#include "CLI.h"

#include "help.h"
#include "init.h"

CLI* CLI::s_instance = nullptr;

CLI::CliRet CLI::parseArgs(int argc, char** argv){
	if (argc <= 1){ 
		// TODO: search for .peproj file and load return success
		return CliRet::PRJ_NOT_FOUNT; 
	}
	if ( std::string( argv[1]) == std::string("-h")){
		printCliHelp();
		return CliRet::Done;
	}
	else if (std::string(argv[1]) == std::string("init")) {
		if ( cliInit(argc, argv))return CliRet::Error;
		return CliRet::Success;
	}
	else if (std::string(argv[1]) == std::string("clean")) {
		auto clean = py::module::import("clean");
		PE_TRY(clean.attr("clean")());
		return CliRet::Success;
	}
}