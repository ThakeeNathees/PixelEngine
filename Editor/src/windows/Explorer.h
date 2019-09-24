#pragma once

#include <pybind11/embed.h>
namespace py = pybind11;

#include "FileTree.h"
#include "Popups.h"


class Explorer
{
private:
	py::object m_py_explorer;
	py::object m_py_os;
	std::string m_menu_path = ".";
	

public:
	Explorer( const std::string& path) {
		py::module explorer_py = py::module::import("explorer");
		m_py_explorer = explorer_py.attr("Explorer")(path);
		m_py_os = py::module::import("os");
	}

	void render() {
		ImGui::Begin("Explorer");

		ImGui::BeginGroup();
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		
		// path up button
		if (ImGui::ImageButton(Resources::OtherIcons::EXPLORER_UP)) {
			m_py_explorer.attr("pathUp")();
		}
		
		// path text
		std::string path = m_py_explorer.attr("getPath")().cast<std::string>();
		ImGui::Text( path.c_str() );

		ImGui::BeginChild("Child2", ImVec2(ImGui::GetWindowSize().x-15, 400 ), true);


		for ( int i =0; i < m_py_explorer.attr("getItemCount")().cast<int>(); i++  )
		{
			// icon
			std::string item_name = m_py_explorer.attr("getItemName")(i).cast<std::string>();
			if ( m_py_explorer.attr("isItemDir")(i).cast<bool>() ) {
				ImGui::Image(Resources::FileFormatIcons::DIR_CLOSED); ImGui::SameLine();
			}
			else {
				FileTree::drawFileIcon(item_name);
			}
			
			// item
			if ( ImGui::Selectable( item_name.c_str(), false, ImGuiSelectableFlags_AllowDoubleClick)) {
				if (ImGui::IsMouseDoubleClicked(0) && m_py_explorer.attr("isItemDir")(i).cast<bool>()) {
					m_py_explorer.attr("pathIn")(i);
				}
			}
			if (ImGui::IsItemClicked(1)) {
				// Todo:
			}
		}

		ImGui::EndChild();
		ImGui::PopStyleVar();
		ImGui::EndGroup();
		ImGui::End();
	}

private:
	void renderRightMouseMenu(const std::string& path) {
		if (ImGui::BeginPopupContextItem("right mouse menu")) {
			// for folder
			if (m_py_os.attr("path").attr("isdir")(path).cast<bool>()) {

				ImGui::Image(Resources::MenuIcons::NONE); ImGui::SameLine();
				if (ImGui::BeginMenu("New")) {
					ImGui::Image(Resources::FileFormatIcons::_FILE_UNKNOWN); ImGui::SameLine();
					if (ImGui::BeginMenu("File")) {
						ImGui::Text("Create a new file"); ImGui::Separator();
						static char file_name[1024];
						ImGui::Text("Name"); ImGui::SameLine();
						ImGui::InputText("", file_name, sizeof(file_name));
						if (ImGui::IsKeyPressed(sf::Keyboard::Key::Enter)) {
							m_py_os.attr("system")(std::string("copy NUL \"").append(
								m_py_os.attr("path").attr("join")(path, file_name).cast<std::string>()
							).append("\""));  m_py_explorer.attr("reload")(); file_name[0] = 0;
							ImGui::CloseCurrentPopup();
						}
						ImGui::EndMenu();
					}
					ImGui::Image(Resources::FileFormatIcons::DIR_CLOSED); ImGui::SameLine();
					if (ImGui::BeginMenu("Folder")) {
						ImGui::Text("Create a new folder"); ImGui::Separator();
						static char dir_name[1024];
						ImGui::Text("Name"); ImGui::SameLine();
						ImGui::InputText("", dir_name, sizeof(dir_name));
						if (ImGui::IsKeyPressed(sf::Keyboard::Key::Enter)) {
							m_py_os.attr("system")(std::string("mkdir \"").append(
								m_py_os.attr("path").attr("join")(path, dir_name).cast<std::string>()
							).append("\"")); m_py_explorer.attr("reload")(); dir_name[0] = 0;
							ImGui::CloseCurrentPopup();
						}
						ImGui::EndMenu();
					}
					ImGui::EndMenu();
				}

				ImGui::Image(Resources::MenuIcons::RENAME); ImGui::SameLine();
				if (ImGui::BeginMenu("Rename")) {
					ImGui::Text("rename folder"); ImGui::Separator();
					static char new_name[1024];
					ImGui::Text("Name"); ImGui::SameLine();
					ImGui::InputText("", new_name, sizeof(new_name));
					if (ImGui::IsKeyPressed(sf::Keyboard::Key::Enter)) {
						m_py_os.attr("system")(std::string("rename \"").append(path).append("\" \"").append(new_name).append("\""));
						m_py_explorer.attr("reload")(); new_name[0] = 0;
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndMenu();
				}

				ImGui::Image(Resources::MenuIcons::_DELETE); ImGui::SameLine();
				if (ImGui::Selectable("Delete")) {
					m_py_explorer;
					Popups::PopupData data; data.path = path; data.is_path_dir = true;
					Popups::openPopup("Delete Conformation", data);
				}

				ImGui::Image(Resources::MenuIcons::OPEN_IN_EXPLORER); ImGui::SameLine();
				if (ImGui::Selectable("Open in explorer")) {
					m_py_os.attr("system")(std::string("explorer \"").append(path).append("\""));
				}
			}
			// for files
			else {

				ImGui::Image(Resources::MenuIcons::RENAME); ImGui::SameLine();
				if (ImGui::BeginMenu("Rename")) {
					ImGui::Text("rename folder"); ImGui::Separator();
					static char new_name[1024];
					ImGui::Text("Name"); ImGui::SameLine();
					ImGui::InputText("", new_name, sizeof(new_name));
					if (ImGui::IsKeyPressed(sf::Keyboard::Key::Enter)) {
						m_py_os.attr("system")(std::string("rename \"").append(path).append("\" \"").append(new_name).append("\""));
						m_py_explorer.attr("reload")(); new_name[0] = 0;
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndMenu();
				}

				ImGui::Image(Resources::MenuIcons::_DELETE); ImGui::SameLine();
				if (ImGui::Selectable("Delete")) {
					Popups::PopupData data; data.path = path; data.is_path_dir = false;
					Popups::openPopup("Delete Conformation", data);
				}

				ImGui::Image(Resources::MenuIcons::OPEN_IN_EXPLORER); ImGui::SameLine();
				if (ImGui::Selectable("Open in explorer")) {
					m_py_os.attr("system")(std::string("explorer \"").append(
						m_py_os.attr("path").attr("dirname")(path).cast<std::string>()
					).append("\""));
				}
			}
			ImGui::EndPopup();

		}
	}

};