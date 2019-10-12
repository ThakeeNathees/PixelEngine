#include "pch.h"
#include "FileTree.h"

// cpp include
#include "windows/projerty_editor/ObjPropEditor.h"


void FileTree::renderObjectTree(const std::string& path) {
	long long id = PyUtils::getInstance()->getMathUtil().attr("md5Hash")(path, "long").cast<long long>();
	auto file_name = PyUtils::getInstance()->getOs().attr("path").attr("basename")(path).cast<std::string>();
	file_name = PyUtils::getInstance()->getStrUtil().attr("getFileName")(file_name).cast<std::string>();
	float dir_icon_pos = ImGui::GetCursorPosX();

	if (m_objects.find(id) == m_objects.end()) {
		auto obj_tag = m_object_reader.attr("ObjectTag")(path);
		m_objects[id] = obj_tag;
	}
	auto& obj_tag = m_objects[id];

	if (ImGui::TreeNode(path.c_str(), file_name.c_str())) { // tree begins
		ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
		// right click
		if (ImGui::IsItemClicked(1))
			m_selected_menu_id = id;
		if (id == m_selected_menu_id) renderRightMouseMenuObject(path, id);
		ImGui::SameLine(); ImGui::SetCursorPosX(dir_icon_pos); ImGui::Image(Resources::getFileFormatIcon("object_file"));

		
		if (obj_tag.attr("hasSpriteTag")().cast<bool>()) {
			ImGui::Image(Resources::getFileFormatIcon("obj_sprite")); ImGui::SameLine();
			ImGui::SetCursorPosX(ImGui::GetCursorPosX() - 20);
			if(ImGui::TreeNodeEx("Sprite", node_flags)){}
			//if(ImGui::TreeNodeEx(obj_tag.attr("getSpriteTag")().attr("attrib").attr("__getitem__")("name").cast<std::string>().c_str(), node_flags)){}
		}
		
		if (obj_tag.attr("hasAreaTag")().cast<bool>()) {
			ImGui::Image(Resources::getFileFormatIcon("obj_area")); ImGui::SameLine();
			ImGui::SetCursorPosX(ImGui::GetCursorPosX() - 20);
			if (ImGui::TreeNodeEx("Area", node_flags)) {}
			//if (ImGui::TreeNodeEx(obj_tag.attr("getAreaTag")().attr("attrib").attr("__getitem__")("name").cast<std::string>().c_str(), node_flags)) {}
		}

		if (obj_tag.attr("hasAnyAnimations")().cast<bool>()) {
			ImGui::Image(Resources::getFileFormatIcon("obj_animation")); ImGui::SameLine();
			ImGui::SetCursorPosX(ImGui::GetCursorPosX() - 20);
			if (ImGui::TreeNodeEx("Animations", node_flags)) {}
			//if (ImGui::TreeNodeEx(obj_tag.attr("getAreaTag")().attr("attrib").attr("__getitem__")("name").cast<std::string>().c_str(), node_flags)) {}
		}
		


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


		if (ImGui::Selectable("Edit")) {
			ObjPropEditor::getinstance()->setObjTag(&m_objects[id]);
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
