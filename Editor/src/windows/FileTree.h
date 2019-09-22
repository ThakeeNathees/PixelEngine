#pragma once

#include "../core/cli/CLI.h"
#include "../core/Resources.h"
#include "TextEditors.h"
#include "HexEditors.h"
#include "FontViwers.h"

#include <pybind11/stl.h>
#include "pybind11/embed.h"
namespace py = pybind11;

class FileTree
{
private:
	FileTree(const std::string& title)
		: m_title(title)
	{
		auto m = py::module::import("file_tree");
		m_py_filetree = m.attr("FileTree")(CLI::getCwd());
		m_py_os = py::module::import("os");
		m_math_util = py::module::import("math_util"); // make it static like
	}

	static FileTree* s_instance;
	std::string m_title;
	py::object m_py_os;
	py::object m_py_filetree;
	py::object m_math_util;
	long long m_selected_id = -1;
	long long m_selected_menu_id = -1;


public:
	static FileTree* getInstance() {
		if (!s_instance) s_instance = new FileTree("Project-Explorer");
		return s_instance;
	}

	void reload() {
		auto m = py::module::import("file_tree");
		m_py_filetree = m.attr("FileTree")(CLI::getCwd());
	}
	
	void render() {
		ImGui::Begin(m_title.c_str());
		int dir_ind = 0;
		renderTreeRecursive(m_py_filetree, true);
		ImGui::End();

	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////
private:
	void renderTreeRecursive(py::object& tree, bool next_item_open = false);
	void drawFileIcon(const std::string& path);
	void nodeClickedEvent(const std::string& title, const std::string& path, long long id=-1);
	void renderRightMouseMenu(const std::string& path);

};
