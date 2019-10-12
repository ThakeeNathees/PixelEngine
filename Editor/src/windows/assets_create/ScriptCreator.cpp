#include "pch.h"
#include "ScriptsCreator.h"

// cpp include
#include "windows/file_tree/FileTree.h"

ScriptCreator* ScriptCreator::s_instance = nullptr;

void ScriptCreator::render()
{
	if (m_popen) {

		ImGui::Begin("Create New Script", &m_popen);
		ImGui::SetWindowSize(ImVec2(400, 220), ImGuiCond_Once);

		static float witdh_frac = .6f;

		// title
		ImGui::Text("Create a new Script Here"); ImGui::Text("");

		// script name
		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * witdh_frac);
		ImGui::InputText("script name", m_script_name, sizeof(m_script_name));
		// script path select
		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * witdh_frac);
		if (ImGui::InputText("script path   ", m_script_path, sizeof(m_script_path))) {
		}
		ImGui::SameLine();
		static auto obj_path_button = Resources::getFileFormatIcon("dir_open");
		if (ImGui::ImageButton(obj_path_button)) {
			ExplorerPopup::getInstance()->setPath(".");
			ImGui::OpenPopup("Explorer");
			ExplorerPopup::getInstance()->setParentWindow(2);
		}

		// scr type combo
		const char* scr_type[] = { "PYTHON","C++" };
		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * witdh_frac);
		if (ImGui::Combo("script type", &m_script_type, scr_type, (int)(sizeof(scr_type) / sizeof(const char*)))) {}

		// template type combo
		const char* template_type[] = { "Default","No Comments","Empty" };
		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * witdh_frac);
		if (ImGui::Combo("template type", &m_template_type, template_type, (int)(sizeof(template_type) / sizeof(const char*)))) {}

		/************************		end of input fields		********************/
		// create button
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 20);
		if (ImGui::Button("Create", ImVec2(-1, 20))) {
			auto str_scr_path = std::string(m_script_path); // char array to string
			if (m_script_name[0] == '\0' || m_script_path[0] == '\0')
				ImGui::OpenPopup("Error!");
			else if (!PyUtils::getInstance()->getStrUtil().attr("isValidName")(std::string(m_script_name)).cast<bool>())
				ImGui::OpenPopup("Invalid Script Name!");
			else if (!PyUtils::getInstance()->getOs().attr("path").attr("isdir")(std::string(m_script_path)).cast<bool>())
				ImGui::OpenPopup("Invalid Script Path!");
			else {
				m_script_path_name = PyUtils::getInstance()->getFileUtil().attr("createScript")(std::string(m_script_path), std::string(m_script_name), m_script_type, m_template_type ).cast<std::string>();
				FileTree::getInstance()->reload();
				m_popen = false;
				m_is_script_created = true;
			}
		}

		// render popups
		ExplorerPopup::getInstance()->render();

		if (ImGui::BeginPopupModal("Error!")) {
			ImGui::SetWindowSize(ImVec2(300, 120), ImGuiCond_Once);
			ImGui::Image(Resources::getOtherIcon("error")); ImGui::SameLine();
			if (m_script_name[0] == '\0') ImGui::TextWrapped("Error! enter a Script Name!");
			else ImGui::TextWrapped("Error! enter the script Path!");
			if (ImGui::Button("OK", ImVec2(280, 20))) {
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
		if (ImGui::BeginPopupModal("Invalid Script Path!")) {
			ImGui::SetWindowSize(ImVec2(300, 120), ImGuiCond_Once);
			ImGui::Image(Resources::getOtherIcon("error")); ImGui::SameLine();
			ImGui::TextWrapped("Error! script path is invalid");
			if (ImGui::Button("OK", ImVec2(280, 20))) {
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
		if (ImGui::BeginPopupModal("Invalid Script Name!")) {
			ImGui::SetWindowSize(ImVec2(300, 140), ImGuiCond_Once);
			ImGui::Image(Resources::getOtherIcon("error")); ImGui::SameLine();
			ImGui::TextWrapped("Error! script name is invalid. (script name must start with alphabatic character and doesn't contain any of the following \\ / : * ? \" < > | spacebar)");
			if (ImGui::Button("OK", ImVec2(280, 20))) {
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}


		// capture selected path to inputs
		if (ExplorerPopup::getInstance()->isPathSelected() && ExplorerPopup::getInstance()->getParentWindow() == 2) {
			ExplorerPopup::getInstance()->setParentWindow(-1);
			auto rel_path = PyUtils::getInstance()->getFileUtil().attr("relPath")(ExplorerPopup::getInstance()->getSelectedPath()).cast<std::string>();
			const char* c = rel_path.c_str();
			int i = 0; // to copy string
			while (c[i])  m_script_path[i] = c[i++]; m_script_path[i] = 0;
			ExplorerPopup::getInstance()->setPathSelectedFalse();
		}

		ImGui::End();
	}
}