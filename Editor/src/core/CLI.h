#pragma once

#include "Console.h"
#include "core/PyUtils.h"

class CLI
{
public:

	// getters
	static CLI* getInstance() {
		if (!s_instance) s_instance = new CLI();
		return s_instance;
	}
	static std::string getExecPath() { return s_exec_path; }
	static const std::string getCwd();
	Console* getConsole() {
		return m_console;
	}
	std::string getProjFileName() const { return m_proj_file_name; }
	pe::_peproj& getPeproj() { return m_peproj; }
	// setters

	// methods
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
	int projFileUpdate(bool include_pe = true, const std::string& proj_dir=".") {
		int error = 0;
		try {
			m_py_proj_init.attr("updateProj")(m_proj_file_name, proj_dir, include_pe);
			PE_LOG("CLI::projUpdate success");
			auto pypaths = PyUtils::getInstance()->getFileUtil().attr("getPyPaths")().cast<std::vector<std::string>>();
			for (std::string& pypath : pypaths) {
				py::exec(std::string("if '").append(pypath).append("'not in sys.path : sys.path.append('").append(pypath).append("')"));
			}
		}
		catch (const std::exception&e){
			PE_LOG("\nERROR: in method CLI::projUpdate\n%s\n",e.what());
			error = 1;
		}
		return error;
	}
	void assetsFileUpdate() {
		m_py_proj_init.attr("updateAssets")(); // TODO: default smooth ... 
		Resources::readAssets();
	}

	void updateTexture(pe::Texture* tex) {
		if (tex == nullptr) {
			PE_CONSOLE_LOG("Error: CLI::updateTexture called with nullptr");
			return;
		}
		m_py_assets_updater.attr("modifyTexture")(tex->getId(), tex->getName(), tex->isSmooth(), tex->isRepeated());
	}
	
	int readProjFile(); // read and update the m_proj at the begining
	int updatePeproj(); // updates the m_peproj;

	static void parseArgs(int argc, char** argv);
	static void log(const std::string log_msg, Console::LogLevel log_level = Console::LOGLEVEL_INFO) {
		getInstance()->getConsole()->addLog(log_msg, log_level);
	}
	static void save(const std::string& text_to_save, const std::string& file_path);

	static void chDir(const std::string& path);
	static int readTextFile(std::string& out, const std::string& path);
	static int readBinaryFile(std::vector<unsigned char>& buffer, const std::string& path);

private:
	CLI() {}
	static std::pair<std::string,std::vector<std::string>> getKeyValue(const std::string& line);
	static CLI* s_instance;
	static std::string s_exec_path;

	std::string m_proj_file_name;
	pe::_peproj m_peproj;

	Console* m_console; // TODO: delete
	void readPeConfigFile();
	py::module m_py_os;
	py::module m_py_proj_init;
	py::module m_py_assets_updater;
};
