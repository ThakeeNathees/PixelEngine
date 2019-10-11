#pragma once

#include "core/CLI.h"
#include "windows/views/TextEditors.h"
#include "windows/views/HexEditors.h"
#include "windows/views/FontViwers.h"
#include "windows/views/ImageViwers.h"

class FileTree
{
private:
	FileTree(const std::string& title)
		: m_title(title)
	{
		auto m = py::module::import("file_tree");
		m_py_filetree = m.attr("FileTree")(CLI::getCwd());
	}

	static FileTree* s_instance;
	std::string m_title;
	py::object m_py_filetree;
	long long m_selected_id = -1;
	long long m_selected_menu_id = -1;

	bool m_open_popup = false;
	std::string m_delete_path = "";
	bool m_is_deletepathdir = false;


public:
	bool m_open = true; // main menu bar need &m_open
	static FileTree* getInstance() {
		if (!s_instance) s_instance = new FileTree("Project-Explorer");
		return s_instance;
	}

	void reload() {
		auto m = py::module::import("file_tree");
		m_py_filetree = m.attr("FileTree")(CLI::getCwd());
	}
	
	void render() {
		if (m_open) {
			ImGui::Begin(m_title.c_str(), &m_open);
			renderTreeRecursive(m_py_filetree, true);
			renderPopup();
			ImGui::End();
		}
	}


	py::object& getPyFileTree() {
		return m_py_filetree;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////
	//static void drawFileIcon(const std::string& path);
private:
	void renderTreeRecursive(py::object& tree, bool next_item_open = false);
	void renderAssetsTree(const std::string& path);
	void renderObjectTree(const std::string& path);
	void renderRightMouseMenuTexture(int texture_id);

	void renderPopup();
	void nodeClickedEvent(const std::string& title, const std::string& path, long long id=-1);
	void renderRightMouseMenu(const std::string& path);
	void renderRightMouseMenuAssets(const std::string& path, long long id);
	void renderRightMouseMenuObject(const std::string& path, long long id);

};
