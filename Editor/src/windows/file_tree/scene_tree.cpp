#include "pch.h"

#include "pch.h"
#include "FileTree.h"

#include "windows/projerty_editor/ScenePropEditor.h"


void FileTree::renderSceneTree(const std::string& path) {
	long long id = PyUtils::getInstance()->getMathUtil().attr("md5Hash")(path, "long").cast<long long>();
	auto file_name = PyUtils::getInstance()->getOs().attr("path").attr("basename")(path).cast<std::string>();
	file_name = PyUtils::getInstance()->getStrUtil().attr("getFileName")(file_name).cast<std::string>();

	if (m_scenes.find(id) == m_scenes.end()) {
		auto scn_tag = m_scene_reader.attr("SceneTag")(path);
		m_scenes[id] = scn_tag;
	}
	auto& scn_tag = m_scenes[id];

	float dir_icon_pos = ImGui::GetCursorPosX();
	if (ImGui::TreeNode(path.c_str(), file_name.c_str())) { // tree begins
		ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;

		// right click
		if (ImGui::IsItemClicked(1))
			m_selected_menu_id = id;
		if (id == m_selected_menu_id) renderRightMouseMenuScene(path, id);
		ImGui::SameLine(); ImGui::SetCursorPosX(dir_icon_pos); ImGui::Image(Resources::getFileFormatIcon("scene_file"));

		// background
		if (scn_tag.attr("hasBgTag")().cast<bool>()) {
			ImGui::Image(Resources::getFileFormatIcon("scene_bg")); ImGui::SameLine();
			ImGui::SetCursorPosX(ImGui::GetCursorPosX() - 20);
			if (ImGui::TreeNodeEx("Background", node_flags)) {}

			// click node
			if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0)) {
				ScenePropEditor::getInstance()->open( &m_scenes[id] );
			}
			if (ImGui::IsItemClicked(0)) m_selected_id = id;
			if (ImGui::IsItemClicked(1)) m_selected_menu_id = id;
			if (id == m_selected_menu_id) renderRightMouseMenuSprite(id);
		}

		// TODO: add object references

		ImGui::TreePop();
	}
	else { // object close
		if (ImGui::IsItemClicked(1)) m_selected_menu_id = id;
		if (id == m_selected_menu_id) renderRightMouseMenuScene(path, id);
		ImGui::SameLine(); ImGui::SetCursorPosX(dir_icon_pos); ImGui::Image(Resources::getFileFormatIcon("scene_file"));

	}
}



void FileTree::renderRightMouseMenuScene(const std::string& path, long long id) {
	if (ImGui::BeginPopupContextItem("right mouse menu")) {

		if (ImGui::Selectable("Edit")) {
			ScenePropEditor::getInstance()->open(&m_scenes[id]);
		}

		if (ImGui::Selectable("Open in TextEditor")) {
			std::string title = PyUtils::getInstance()->getOs().attr("path").attr("basename")(path).cast<std::string>();
			TextEditors::openTextEditor(title, path, id, TextEditor::LanguageDefinition::C());
		}

		ImGui::Image(Resources::getMenuIcon("open_in_explorer")); ImGui::SameLine();
		if (ImGui::Selectable("Open in Explorer")) {
			PyUtils::getInstance()->getOs().attr("system")(std::string("explorer \"").append(
				PyUtils::getInstance()->getOs().attr("path").attr("dirname")(path).cast<std::string>()
			).append("\""));
		}

		ImGui::EndPopup();
	}
}
