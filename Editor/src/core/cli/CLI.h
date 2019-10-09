#pragma once
#include "..//Console.h"
#include "pybind11/stl.h"
#include "pyutils/PyUtils.h"

class CLI
{
public:

	void init();
	void projInit(const std::string& path, const std::string& name ) {
		try {
			m_py_proj_init.attr("init")(name, path);
			PE_LOG("CLI::projInit success");
		}
		catch (const std::exception& e){
			PE_LOG("\nERROR: in mehtod CLI::projInit \n%s\n", e.what());
		}
	}
	void projUpdate(bool include_pe = true, const std::string& proj_name="", const std::string& proj_dir=".") {
		try {
			auto ret = m_py_proj_init.attr("updateProj")(proj_name, proj_dir, include_pe);
			PE_LOG("CLI::projUpdate success");
			auto pypaths = PyUtils::getInstance()->getFileUtil().attr("getPyPaths")().cast<std::vector<std::string>>();
			for (std::string& pypath : pypaths) {
				py::exec(std::string("sys.path.append('").append(pypath).append("')"));
			}
			PE_LOG("CLI::projUpdate python paths append success");
		}
		catch (const std::exception&e){
			PE_LOG("\nERROR: in method CLI::projUpdate\n%s\n",e.what());
		}
	}

	void updateTexture(pe::Texture* tex) {
		if (tex == nullptr) {
			PE_CONSOLE_LOG("Error: CLI::updateTexture called with nullptr");
			return;
		}
		m_py_assets_updater.attr("modifyTexture")(tex->getId(), tex->getName(), tex->isSmooth(), tex->isRepeated());
	}

	static void parseArgs(int argc, char** argv);
	static void log(const std::string log_msg, Console::LogLevel log_level = Console::LOGLEVEL_INFO) {
		getInstance()->getConsole()->addLog(log_msg, log_level);
	}
	static CLI* getInstance() {
		if (!s_instance) s_instance = new CLI();
		return s_instance;
	}
	static void save(const std::string& text_to_save, const std::string& file_path);
	static std::string getExecPath() { return s_exec_path; }
	static const std::string getCwd();
	static void chDir(const std::string& path);
	static int readTextFile(std::string& out, const std::string& path);
	static int readBinaryFile(std::vector<unsigned char>& buffer, const std::string& path);

	Console* getConsole() {
		return m_console;
	}

private:
	CLI() {}
	static std::pair<std::string,std::vector<std::string>> getKeyValue(const std::string& line);
	static CLI* s_instance;
	static std::string s_exec_path;

	Console* m_console; // TODO: delete
	void readPeConfigFile();
	py::module m_py_os;
	py::module m_py_proj_init;
	py::module m_py_assets_updater;
};
