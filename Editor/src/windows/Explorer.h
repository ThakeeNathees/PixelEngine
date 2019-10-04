#pragma once
#include "FileTree.h"


class ExplorerPopup
{
private:
	bool m_p_open = true;
	bool m_is_path_selected = false;
	std::string m_selected_path = "";
	py::object m_py_explorer;
	ExplorerPopup( const std::string& path) {
		py::module explorer_py = py::module::import("explorer");
		m_py_explorer = explorer_py.attr("Explorer")(path);
	}
	static ExplorerPopup* s_instance;
	int m_selected = -1;

public:
	static ExplorerPopup* getInstance() {
		if (s_instance == nullptr)  s_instance = new ExplorerPopup("C:/");
		return s_instance;
	}

	void setPathSelectedFalse() {
		m_is_path_selected = false;
	}
	bool isPathSelected() {
		return m_is_path_selected;
	}
	const std::string& getSelectedPath() {
		return m_selected_path;
	}

	std::string getPath() {
		return m_py_explorer.attr("getPath")().cast<std::string>();
	}
	void setPath(const std::string& path) {
		m_py_explorer.attr("setPath")( path );
		m_py_explorer.attr("reload")();
	}

	void render(bool is_select_dir = true) {
		if (!ImGui::IsPopupOpen("Explorer")) m_p_open = true;
		if (ImGui::BeginPopupModal("Explorer", &m_p_open)) {

			if (!m_p_open) ImGui::CloseCurrentPopup();

			ImGui::SetWindowSize(ImVec2(800, 400), ImGuiCond_Once);

			ImGui::BeginGroup();
			ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);

			// path up button
			if (ImGui::ImageButton(Resources::OtherIcons::EXPLORER_UP)) {
				m_py_explorer.attr("pathUp")();
			}
			ImGui::SameLine();
			if (ImGui::ImageButton(Resources::OtherIcons::EXPLORER_REFRESH)) {
				m_py_explorer.attr("reload")();
			}
			ImGui::SameLine();
			const char* drives[] = {"C:/","D:/","E:/"};
			static int current_drive = 0; // C:/
			if (ImGui::Combo("drive", &current_drive, drives, (int)(sizeof(drives) / sizeof(const char*)))) {
				m_py_explorer.attr("setPath")( std::string(drives[current_drive]) );
				m_py_explorer.attr("reload")();
			}


			// path text
			std::string path = m_py_explorer.attr("getPath")().cast<std::string>();
			ImGui::Text(path.c_str());

			ImGui::BeginChild("Child2", ImVec2(ImGui::GetWindowSize().x - 15, ImGui::GetWindowSize().y - ImGui::GetCursorPosY() - 50), true);


			for (int i = 0; i < m_py_explorer.attr("getItemCount")().cast<int>(); i++)
			{
				// icon
				std::string item_name = m_py_explorer.attr("getItemName")(i).cast<std::string>();
				if (m_py_explorer.attr("isItemDir")(i).cast<bool>()) {
					ImGui::Image(Resources::FileFormatIcons::DIR_CLOSED); ImGui::SameLine();
				}
				else {
					FileTree::drawFileIcon(item_name);
				}

				// item
				if (ImGui::Selectable(item_name.c_str(), m_selected == i, ImGuiSelectableFlags_AllowDoubleClick)) {
					m_selected = i;
					if (ImGui::IsMouseDoubleClicked(0)) {
						if (m_py_explorer.attr("isItemDir")(i).cast<bool>()) {
							m_selected = -1;
							m_py_explorer.attr("pathIn")(i);
						}
						else if(!is_select_dir) {
							m_is_path_selected = true;
							m_selected_path = m_py_explorer.attr("getItemPath")(i).cast<std::string>();
							m_selected = -1;
							ImGui::CloseCurrentPopup();
						}
					}
				}
			}
			ImGui::EndChild();
			ImGui::PopStyleVar();

			// button for dir select and file select
			if (is_select_dir) {
				if (ImGui::Button("Select this folder")) {
					m_is_path_selected = true;
					if (m_selected < 0 ) m_selected_path = m_py_explorer.attr("getPath")().cast<std::string>();
					else if (m_selected >=0 && ! m_py_explorer.attr("isItemDir")(m_selected).cast<bool>()) m_selected_path = m_py_explorer.attr("getPath")().cast<std::string>();
					else m_selected_path = m_selected_path = m_py_explorer.attr("getItemPath")(m_selected).cast<std::string>();
					m_selected = -1;
					ImGui::CloseCurrentPopup();
				}
			}
			else {
				if (ImGui::Button("Select this file")) {
					if (m_selected > 0) {
						m_is_path_selected = true;
						m_selected_path = m_py_explorer.attr("getItemPath")(m_selected).cast<std::string>();
						m_selected = -1;
						ImGui::CloseCurrentPopup();
					}
				}
			}

			ImGui::SameLine();
			if (ImGui::Button("Cencel")) {
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndGroup();
			ImGui::EndPopup();
		}
	}

private:
	
};