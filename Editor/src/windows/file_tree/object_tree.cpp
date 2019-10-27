#include "pch.h"
#include "FileTree.h"

// cpp include
#include "windows/projerty_editor/ObjPropEditor.h"
#include "windows/projerty_editor/SpritePropEditor.h"
#include "windows/projerty_editor/AreaPropEditor.h"


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

		// sprite
		if (obj_tag.attr("hasSpriteTag")().cast<bool>()) {
			ImGui::Image(Resources::getFileFormatIcon("obj_sprite")); ImGui::SameLine();
			ImGui::SetCursorPosX(ImGui::GetCursorPosX() - 20);
			if(ImGui::TreeNodeEx("Sprite", node_flags)){}
			
			// click node
			if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0)) {
				SpritePropEditor::getInstance()->open(&m_objects[id]);
			}
			if (ImGui::IsItemClicked(0)) m_selected_id = id;
			if (ImGui::IsItemClicked(1)) m_selected_menu_id = id;
			if (id == m_selected_menu_id) renderRightMouseMenuSprite(id);
		}
		
		// area
		if (obj_tag.attr("hasAreaTag")().cast<bool>()) {
			ImGui::Image(Resources::getFileFormatIcon("obj_area")); ImGui::SameLine();
			ImGui::SetCursorPosX(ImGui::GetCursorPosX() - 20);
			if (ImGui::TreeNodeEx("Area", node_flags)) {}

			// click node
			if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0)) {
				AreaPropEditor::getInstance()->open(&m_objects[id]);
			}
			if (ImGui::IsItemClicked(1)) m_selected_menu_id = id;
			if (id == m_selected_menu_id) renderRightMouseMenuArea(id);
			//if (ImGui::TreeNodeEx(obj_tag.attr("getAreaTag")().attr("attrib").attr("__getitem__")("name").cast<std::string>().c_str(), node_flags)) {}
		}

		// animations
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
			ObjPropEditor::getInstance()->setObjTag(&m_objects[id]);
		}

		// sprite
		if (!m_objects[id].attr("hasSpriteTag")().cast<bool>()) {
			if (ImGui::MenuItem("New Sprite")) {
				int spr_id = CLI::getInstance()->getPeproj().next_sprite_id++;
				m_objects[id].attr("createSprite")(spr_id);
				m_objects[id].attr("save")();
			}
		}
		else {
			if (ImGui::MenuItem("Delete Sprite")) {
				m_open_popup_sprite = true;
				m_delete_conform_obj_id = id;
				//m_objects[id].attr("deleteSprite")();
				//m_objects[id].attr("save")();
			}
		}

		// area
		if (!m_objects[id].attr("hasAreaTag")().cast<bool>()) {
			if (ImGui::MenuItem("New Area")) {
				int area_id = CLI::getInstance()->getPeproj().next_area_id++;
				m_objects[id].attr("createArea")(area_id);
				m_objects[id].attr("save")();
			}
		}
		else {
			if (ImGui::MenuItem("Delete Area")) {
				m_open_popup_area = true;
				m_delete_conform_obj_id = id;
				//m_objects[id].attr("deleteArea")();
				//m_objects[id].attr("save")();
			}
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


void FileTree::renderRightMouseMenuSprite(long long id) {
	if (ImGui::BeginPopupContextItem("right mouse sprite")) {
		if (ImGui::Selectable("Edit")) {
			SpritePropEditor::getInstance()->open(&m_objects[id]);
		}
		if (ImGui::MenuItem("Delete Sprite")) {
			m_open_popup_sprite = true;
			m_delete_conform_obj_id = id;
		}
		ImGui::EndPopup();
	}
}

void FileTree::renderRightMouseMenuArea(long long id) {
	if (ImGui::BeginPopupContextItem("right mouse area")) {
		if (ImGui::Selectable("Edit")) {
			AreaPropEditor::getInstance()->open(&m_objects[id]);
		}
		if (ImGui::MenuItem("Delete Area")) {
			m_open_popup_area = true;
			m_delete_conform_obj_id = id;
		}

		ImGui::EndPopup();
	}
}

