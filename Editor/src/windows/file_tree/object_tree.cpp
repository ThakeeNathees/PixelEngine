#include "pch.h"
#include "FileTree.h"


void FileTree::renderObjectTree(const std::string& path) {
	long long id = PyUtils::getInstance()->getMathUtil().attr("md5Hash")(path, "long").cast<long long>();
	std::string dir_name = PyUtils::getInstance()->getOs().attr("path").attr("basename")(path).cast<std::string>();
	float dir_icon_pos = ImGui::GetCursorPosX();


	if (ImGui::TreeNode(path.c_str(), dir_name.c_str())) { // tree begins

		// right click
		if (ImGui::IsItemClicked(1))
			m_selected_menu_id = id;
		if (id == m_selected_menu_id) renderRightMouseMenuObject(path, id);
		ImGui::SameLine(); ImGui::SetCursorPosX(dir_icon_pos); ImGui::Image(Resources::getFileFormatIcon("object_file"));

		if (m_objects.find(id) == m_objects.end()) {
			m_objects[id] = m_object_reader.attr("Object")(path);
		}

		ImGui::Text("test");


		ImGui::TreePop();
	}
	else { // object close
		if (ImGui::IsItemClicked(1)) m_selected_menu_id = id;
		if (id == m_selected_menu_id) renderRightMouseMenuObject(path, id);
		ImGui::SameLine(); ImGui::SetCursorPosX(dir_icon_pos); ImGui::Image(Resources::getFileFormatIcon("object_file"));
	}
}



void FileTree::renderRightMouseMenuObject(const std::string& path, long long id) {
	if (ImGui::BeginPopupContextItem("right mouse menu")) {

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
