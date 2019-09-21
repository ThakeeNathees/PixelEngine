#pragma once

#include "CLI.h"
#include "..//Resources.h"

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

public:
	static FileTree* getInstance() {
		if (!s_instance) s_instance = new FileTree("Project-Explorer");
		return s_instance;
	}

	
	void render() {
		ImGui::Begin(m_title.c_str());
		int dir_ind = 0;
		renderTreeRecursive(m_py_filetree, true);
		ImGui::End();
	}

private:
	void renderTreeRecursive(py::object& tree, bool next_item_open = false) {
		std::string path = tree.attr("path").cast<std::string>();
		std::string dir_name = m_py_os.attr("path").attr("basename")(path).cast<std::string>();
		
		float dir_icon_pos = ImGui::GetCursorPosX();
		if (next_item_open) ImGui::SetNextItemOpen(true, ImGuiCond_Once);
		if (ImGui::TreeNode(path.c_str(), dir_name.c_str())) {
			// draw folder icon
			ImGui::SameLine();ImGui::SetCursorPosX(dir_icon_pos);ImGui::Image(Resources::Icons::DIR_OPEN);
			// loop for dirs
			for (int i = 0; i < tree.attr("dirs").attr("__len__")().cast<int>(); i++) {
				auto sub_tree = tree.attr("dirs").attr("__getitem__")(i);
				renderTreeRecursive(sub_tree);
			}
			// loop for files
			for (int i = 0; i < tree.attr("files").attr("__len__")().cast<int>(); i++) {
				std::string path = tree.attr("files").attr("__getitem__")(i).cast<std::string>();
				long long id = m_math_util.attr("md5Hash")(path, "long").cast<long long>();
				ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
				if (m_slected_id == id) node_flags |= ImGuiTreeNodeFlags_Selected;
				// draw file icon
				ImGui::SetCursorPosX(ImGui::GetCursorPosX()+20);
				drawFileIcon(path);

				ImGui::SetCursorPosX(ImGui::GetCursorPosX() - 20);
				ImGui::TreeNodeEx((void*)(intptr_t)(id), node_flags, m_py_os.attr("path").attr("basename")(path).cast<std::string>().c_str());
				if (ImGui::IsItemClicked()) {
					m_slected_id = id;
				}
			}
			ImGui::TreePop();
		}
		else {
			ImGui::SameLine(); ImGui::SetCursorPosX(dir_icon_pos); ImGui::Image(Resources::Icons::DIR_CLOSED);
		}
	} // recursive render

	void drawFileIcon(const std::string& path) {
		std::string format = m_py_filetree.attr("getFileFormat")(path).cast<std::string>();
		if (format == std::string("py")) { ImGui::Image(Resources::Icons::FILE_PY); ImGui::SameLine();return;}
		if (format == std::string("peproj")) { ImGui::Image(Resources::Icons::FILE_PEPROJ); ImGui::SameLine();return;}
		if (format == std::string("txt")) { ImGui::Image(Resources::Icons::FILE_TEXT); ImGui::SameLine();return;}
		if (format == std::string("xml")) { ImGui::Image(Resources::Icons::FILE_XML); ImGui::SameLine();return;}
		if (format == std::string("pyc")) { ImGui::Image(Resources::Icons::FILE_PYC); ImGui::SameLine();return;}
		if (format == std::string("cpp")) { ImGui::Image(Resources::Icons::FILE_CPP); ImGui::SameLine();return;}
		if (format == std::string("h")) { ImGui::Image(Resources::Icons::FILE_H); ImGui::SameLine();return;}
		if (format == std::string("png")) { ImGui::Image(Resources::Icons::FILE_PNG); ImGui::SameLine();return;}
		if (format == std::string("ttf")) { ImGui::Image(Resources::Icons::FILE_TTF); ImGui::SameLine();return;}
		// binary files
		if (format == std::string("lib") || format == std::string("exe")) {
			ImGui::Image(Resources::Icons::FILE_BIN); ImGui::SameLine();return;
		}
		if (format == std::string("dll")) { ImGui::Image(Resources::Icons::FILE_DLL); ImGui::SameLine();return;}
		if (format == std::string("obj")) { ImGui::Image(Resources::Icons::FILE_OBJ); ImGui::SameLine();return;}

		ImGui::Image(Resources::Icons::_FILE_UNKNOWN); ImGui::SameLine();
	}


private:
	static FileTree* s_instance;
	std::string m_title;
	py::object m_py_os;
	py::object m_py_filetree;
	py::object m_math_util;
	long long m_slected_id = -1;
};
