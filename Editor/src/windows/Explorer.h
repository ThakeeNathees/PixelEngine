#pragma once

#include <pybind11/embed.h>
namespace py = pybind11;

#include "FileTree.h"
#include "Popups.h"


class Explorer
{
private:
	py::object m_py_explorer;
	

public:
	Explorer( const std::string& path) {
		py::module explorer_py = py::module::import("explorer");
		m_py_explorer = explorer_py.attr("Explorer")(path);
	}

	void render() {
		if (ImGui::BeginPopupModal("Explorer")) {

			ImGui::SetWindowSize(ImVec2(800, 400), ImGuiCond_FirstUseEver);

			ImGui::BeginGroup();
			ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);

			// path up button
			if (ImGui::ImageButton(Resources::OtherIcons::EXPLORER_UP)) {
				m_py_explorer.attr("pathUp")();
			}
			ImGui::SameLine();
			if (ImGui::Button("Refresh")) {
				m_py_explorer.attr("reload")();
			}

			// path text
			std::string path = m_py_explorer.attr("getPath")().cast<std::string>();
			ImGui::Text(path.c_str());

			ImGui::BeginChild("Child2", ImVec2(ImGui::GetWindowSize().x - 15, ImGui::GetWindowSize().y*.7), true);


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
				if (ImGui::Selectable(item_name.c_str(), false, ImGuiSelectableFlags_AllowDoubleClick)) {
					if (ImGui::IsMouseDoubleClicked(0) && m_py_explorer.attr("isItemDir")(i).cast<bool>()) {
						m_py_explorer.attr("pathIn")(i);
					}
				}
			}
			ImGui::EndChild();
			ImGui::PopStyleVar();

			if (ImGui::Button("Select this folder")) {
				CLI::getInstance()->projInit(m_py_explorer.attr("getPath")().cast<std::string>());
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