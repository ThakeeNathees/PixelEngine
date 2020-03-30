#include "pch.h"
#include "SceneCreator.h"

// cpp include
#include "windows/file_tree/FileTree.h"

SceneCreator* SceneCreator::s_instance = nullptr;

void SceneCreator::render() {
	
	if (m_open) {

		ImGui::Begin("Create New Script", &m_open);
		ImGui::SetWindowSize(ImVec2(400, 220), ImGuiCond_Once);

		static float witdh_frac = .6f;
		// title
		ImGui::Text("Create a new Scene Here"); ImGui::Text("");

		// scene name
		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * witdh_frac);
		ImGui::InputText("scene name", m_scene_name, sizeof(m_scene_name));

		// script path select
		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * witdh_frac);
		ImGui::InputText("scene path   ", m_scene_path, sizeof(m_scene_path));

		ImGui::SameLine();
		static auto obj_path_button = Resources::getFileFormatIcon("dir_open");
		if (ImGui::ImageButton(obj_path_button)) {
			ExplorerPopup::getInstance()->setPath(".");
			ImGui::OpenPopup("Explorer");
			ExplorerPopup::getInstance()->setParentWindow(2);
		}

		/************************		end of input fields		********************/

		// create button
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 20);
		if (ImGui::Button("Create", ImVec2(-1, 20))) {
			std::string str_scene_path = std::string(m_scene_path); // char array to string
			if (m_scene_name[0] == '\0' || m_scene_name[0] == '\0')
				ImGui::OpenPopup("Error!");
			else if (!PyUtils::getInstance()->getStrUtil().attr("isValidName")(std::string(m_scene_name)).cast<bool>())
				ImGui::OpenPopup("Invalid Scene Name!");
			else if (!PyUtils::getInstance()->getOs().attr("path").attr("isdir")(std::string(m_scene_path)).cast<bool>())
				ImGui::OpenPopup("Invalid Scene Path!");
			else {
				int scn_id = CLI::getInstance()->getPeproj().next_scn_id++;
				//std::string scn_file_path = std::string(m_scene_path).append("/").append(std::string(m_scene_name)).append(".scn.xml");
				// TODO: check path exists, also for object creator

				auto obj_tag = m_py_scn_maker.attr("newScene")(std::string(m_scene_name), scn_id);

				m_py_scn_maker.attr("writeScene")(obj_tag, std::string(m_scene_path));
				int error = CLI::getInstance()->projFileUpdate(false);
				if (error) { CLI::log("Error: in CLI::projFileUpdate(false) -> project file may damaged", Console::LOGLEVEL_ERROR); }

				m_open = false;
				m_is_scene_created = true;
				FileTree::getInstance()->reload();
			}
		}

		// render popups
		ExplorerPopup::getInstance()->render();

		if (ImGui::BeginPopupModal("Error!")) {
			ImGui::SetWindowSize(ImVec2(300, 120), ImGuiCond_Once);
			ImGui::Image(Resources::getOtherIcon("error")); ImGui::SameLine();
			if (m_scene_name[0] == '\0') ImGui::TextWrapped("Error! enter a Scene Name!");
			else ImGui::TextWrapped("Error! enter the Scene Path!");
			if (ImGui::Button("OK", ImVec2(280, 20))) {
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
		if (ImGui::BeginPopupModal("Invalid Scene Path!")) {
			ImGui::SetWindowSize(ImVec2(300, 120), ImGuiCond_Once);
			ImGui::Image(Resources::getOtherIcon("error")); ImGui::SameLine();
			ImGui::TextWrapped("Error! scene path is invalid");
			if (ImGui::Button("OK", ImVec2(280, 20))) {
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
		if (ImGui::BeginPopupModal("Invalid Scene Name!")) {
			ImGui::SetWindowSize(ImVec2(300, 140), ImGuiCond_Once);
			ImGui::Image(Resources::getOtherIcon("error")); ImGui::SameLine();
			ImGui::TextWrapped("Error! scene name is invalid. (scene name must start with alphabatic character and doesn't contain any of the following \\ / : * ? \" < > | spacebar)");
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
			while (c[i])  m_scene_path[i] = c[i++]; m_scene_path[i] = 0;
			ExplorerPopup::getInstance()->setPathSelectedFalse();
		}

		ImGui::End();
	}
}