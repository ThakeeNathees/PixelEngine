#include "pch.h"
#include "Popups.h"

#include "FileTree.h"
#include "..//core/Resources.h"

#include <pybind11/embed.h>
namespace py = pybind11;

std::vector<std::string> Popups::s_open_list;
std::map<std::string, Popups::PopupData> Popups::s_popup_data;


void Popups::renderDeleteConform() {
	if (ImGui::BeginPopupModal("Delete Conformation", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {

		auto py_os = py::module::import("os");
		// folder
		if (s_popup_data["Delete Conformation"].is_path_dir) {
			ImGui::Image(Resources::OtherIcons::WARNING); ImGui::SameLine();
			ImGui::Text("All the files and It's contents \nwill be deleted permenently.\nThis operation cannot be undone!\n\n");
			ImGui::Separator();
			if (ImGui::Button("OK", ImVec2(120, 0))) {
				py_os.attr("system")(std::string("RD /S /Q \"").append(s_popup_data["Delete Conformation"].path).append("\"")); FileTree::getInstance()->reload();
				ImGui::CloseCurrentPopup();
			}
			ImGui::SameLine();
			if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
		}
		else {
			ImGui::Image(Resources::OtherIcons::WARNING); ImGui::SameLine();
			ImGui::Text("The file will be deleted permenently.\nThis operation cannot be undone!\n\n");
			ImGui::Separator();
			if (ImGui::Button("OK", ImVec2(120, 0))) {
				py_os.attr("system")(std::string("del \"").append(s_popup_data["Delete Conformation"].path).append("\"")); FileTree::getInstance()->reload();
				ImGui::CloseCurrentPopup();
			}
			ImGui::SameLine();
			if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
		}

		ImGui::SetItemDefaultFocus();
		ImGui::EndPopup();
	}
}
