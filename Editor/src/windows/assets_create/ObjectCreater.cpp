#include "pch.h"
#include "ObjectCreater.h"
#include "pyutils/PyUtils.h"

ObjectCreater* ObjectCreater::s_instance;

void ObjectCreater::render()
{
	if (m_popen) {
		ImGui::Begin("Create New Object", &m_popen);
		ImGui::SetWindowSize(ImVec2(600, 450), ImGuiCond_Once);

		
		// start title
		ImGui::Text("Create a new Object Here"); ImGui::Text("");

		// start body
		static char obj_name[1024];
		ImGui::InputText("obj_name", obj_name, sizeof(obj_name));

		// object path select
		static char obj_path[1024];
		if (ImGui::InputText("obj_path", obj_path, sizeof(obj_path))) {
		}
		ImGui::SameLine();
		static auto obj_path_button = Resources::FileFormatIcons::DIR_OPEN;
		if (ImGui::ImageButton(obj_path_button)) {
			m_path_dst_ind = 0;
			ExplorerPopup::getInstance()->setPath(".");
			ImGui::OpenPopup("Explorer");
		}
		if (ImGui::IsItemHovered()) ImGui::SetTooltip("select in explorer");

		// script path select
		static char script_path[1024];
		ImGui::InputText("scirpt_path", script_path, sizeof(script_path));
		ImGui::SameLine();
		static auto script_path_button = Resources::FileFormatIcons::DIR_OPEN;
		if (ImGui::ImageButton(script_path_button)) {
			m_path_dst_ind = 1;
			ExplorerPopup::getInstance()->setPath(".");
			ImGui::OpenPopup("Explorer");
		}
		if (ImGui::IsItemHovered()) ImGui::SetTooltip("select in explorer");

		static std::string class_name = "";
		ImGui::Text( std::string("class name : ").append(class_name).c_str() );
		
		static std::string class_type = "PYTHON_OBJECT";
		ImGui::Text( std::string("class type : ").append(class_type).c_str() );
		

		////////

		// create button
		if (ImGui::Button("Create")) {
			auto str_scr_path = std::string(script_path); // char array to string

			if (obj_name[0] == '\0' || obj_path[0] == '\0')
				ImGui::OpenPopup("Error!");
			else if ( ! PyUtils::getInstance()->getStrUtil().attr("isValidName")(std::string(obj_name)).cast<bool>() )
				ImGui::OpenPopup("Invalid Object Name!");
			else if( ! PyUtils::getInstance()->getOs().attr("path").attr("isdir")(std::string(obj_path)).cast<bool>() )
				ImGui::OpenPopup("Invalid Object Path!");

			else if (str_scr_path != std::string("") && !PyUtils::getInstance()->getFileUtil().attr("isPathScript")(str_scr_path).cast<bool>())
				ImGui::OpenPopup("Invalid Script Path!");
			else {
				// TODO: create obj
				FileTree::getInstance()->reload();
				// end and return;
			}

		}
		

		// render popups
		if (m_path_dst_ind==0) ExplorerPopup::getInstance()->render();
		else if (m_path_dst_ind==1) ExplorerPopup::getInstance()->render(false);

		if (ImGui::BeginPopupModal("Error!")) {
			ImGui::SetWindowSize(ImVec2(300, 120), ImGuiCond_Once);
			ImGui::Image(Resources::OtherIcons::_ERROR); ImGui::SameLine();
			if (obj_name[0] == '\0') ImGui::TextWrapped("Error! enter an Object Name!");
			else ImGui::TextWrapped("Error! enter the Object's Path!");
			if (ImGui::Button("OK", ImVec2(280, 20))) {
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
		if (ImGui::BeginPopupModal("Invalid Script Path!")) {
			ImGui::SetWindowSize(ImVec2(300, 120), ImGuiCond_Once);
			ImGui::Image(Resources::OtherIcons::_ERROR); ImGui::SameLine();
			ImGui::TextWrapped("Error! script path is invalid only supported for *.py, *.h, *.hpp");
			if (ImGui::Button("OK", ImVec2(280, 20))) {
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
		if (ImGui::BeginPopupModal("Invalid Object Path!")) {
			ImGui::SetWindowSize(ImVec2(300, 120), ImGuiCond_Once);
			ImGui::Image(Resources::OtherIcons::_ERROR); ImGui::SameLine();
			ImGui::TextWrapped("Error! object path is invalid");
			if (ImGui::Button("OK", ImVec2(280, 20))) {
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
		if (ImGui::BeginPopupModal("Invalid Object Name!")) {
			ImGui::SetWindowSize(ImVec2(300, 140), ImGuiCond_Once);
			ImGui::Image(Resources::OtherIcons::_ERROR); ImGui::SameLine();
			ImGui::TextWrapped("Error! object name is invalid. (object name must start with alphabatic character and doesn't contain any of the following \\ / : * ? \" < > | spacebar)");
			if (ImGui::Button("OK", ImVec2(280, 20))) {
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}

		// capture selected path to inputs
		if (ExplorerPopup::getInstance()->isPathSelected()) {
			const char* c = ExplorerPopup::getInstance()->getSelectedPath().c_str();
			int i = 0; // to copy string
			if (m_path_dst_ind == 0) {
				while (c[i])  obj_path[i] = c[i++]; obj_path[i] = 0;
			}
			else if (m_path_dst_ind == 1) {
					while (c[i])  script_path[i] = c[i++]; script_path[i] = 0;
			}
			ExplorerPopup::getInstance()->setPathSelectedFalse();
		}

		// find class name
		class_name = "test";
		class_type = "CPP_OBJECT";
		//str_scr_path

		ImGui::End();
	}
}