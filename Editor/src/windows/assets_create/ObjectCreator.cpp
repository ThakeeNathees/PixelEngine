#include "pch.h"
#include "ObjectCreator.h"

// cpp include
#include "windows/file_tree/FileTree.h"

ObjectCreater* ObjectCreater::s_instance;

void ObjectCreater::render()
{
	if (m_popen) {
		ImGui::Begin("Create New Object", &m_popen);
		ImGui::SetWindowSize(ImVec2(400, 320), ImGuiCond_Once);

		static float witdh_frac = .6f;
		
		// start title
		ImGui::Text("Create a new Object Here"); ImGui::Text("");

		// object name
		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * witdh_frac);
		ImGui::InputText("object name", m_obj_name, sizeof(m_obj_name));

		// object path select
		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * witdh_frac);
		if (ImGui::InputText("object path   ", m_obj_path, sizeof(m_obj_path))) {
		}
		ImGui::SameLine();
		static auto obj_path_button = Resources::getFileFormatIcon("dir_open");
		if (ImGui::ImageButton(obj_path_button)) {
			m_path_dst_ind = 0;
			ExplorerPopup::getInstance()->setPath(".");
			ImGui::OpenPopup("Explorer");
			ExplorerPopup::getInstance()->setParentWindow(1);
		}

		// script path select
		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * witdh_frac);
		ImGui::InputText("script path", m_script_path, sizeof(m_script_path));
		ImGui::SameLine();
		static auto script_path_button = Resources::getFileFormatIcon("dir_open");
		if (ImGui::ImageButton(script_path_button)) {
			m_path_dst_ind = 1;
			ExplorerPopup::getInstance()->setPath(".");
			ImGui::OpenPopup("Explorer");
			ExplorerPopup::getInstance()->setParentWindow(1);
		}
		ImGui::SameLine();
		if (ImGui::ImageButton(Resources::getOtherIcon("create_new"))) {
			ScriptCreator::getInstance()->m_is_script_created = false;
			ScriptCreator::getInstance()->open();
			ScriptCreator::getInstance()->setParentWindow(0);
		}
		if (ImGui::IsItemHovered()) ImGui::SetTooltip("create a new script");
		
		// class name
		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * witdh_frac);
		ImGui::InputText("script name", m_script_name, sizeof(m_script_name));

		// object type
		static const char* _obj_types[] = { "UNKNOWN","PYTHON_OBJECT", "CPP_OBJECT" };
		static int obj_type = 0;
		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * witdh_frac);
		if (ImGui::Combo("object type", &obj_type, _obj_types, (int)(sizeof(_obj_types) / sizeof(const char*)))) {
			m_obj_type = obj_type;
		}
		
		// zindex, visible, persistence
		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * witdh_frac);
		ImGui::InputInt("z index", &m_z_index);

		static const char* _bool[] = { "false","true"};
		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * witdh_frac);
		if (ImGui::Combo("visible", &m_visible, _bool, (int)(sizeof(_bool) / sizeof(const char*)))) {}
		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * witdh_frac);
		if (ImGui::Combo("persistence", &m_persistance, _bool, (int)(sizeof(_bool) / sizeof(const char*)))) {}

		/************************		end of input fields		********************/

		// create button
		ImGui::SetCursorPosY( ImGui::GetCursorPosY()+20 );
		if (ImGui::Button("Create", ImVec2(-1, 20))) {
			auto str_scr_path = std::string(m_script_path); // char array to string

			if (m_obj_name[0] == '\0' || m_obj_path[0] == '\0')
				ImGui::OpenPopup("Error!");
			else if ( ! PyUtils::getInstance()->getStrUtil().attr("isValidName")(std::string(m_obj_name)).cast<bool>() )
				ImGui::OpenPopup("Invalid Object Name!");
			else if( ! PyUtils::getInstance()->getOs().attr("path").attr("isdir")(std::string(m_obj_path)).cast<bool>() )
				ImGui::OpenPopup("Invalid Object Path!");
			else if (str_scr_path != std::string("") && !PyUtils::getInstance()->getOs().attr("path").attr("exists")(str_scr_path).cast<bool>())
				ImGui::OpenPopup("Invalid Script Path!");
			else {
				int obj_id = CLI::getInstance()->getPeproj().next_obj_id;
				std::string obj_file_path = std::string(m_obj_path).append("/").append(std::string(m_obj_name)).append(".obj.xml");
				
				if (m_script_path[0]) {

					if (m_obj_type == 1) { // python
						m_class_path = PyUtils::getInstance()->getFileUtil().attr("relPyObjDirPath") (m_script_path).cast<std::string>();
						m_pe_obj_type = pe::Object::ObjectType::PYTHON_OBJECT;
					}
					else if (m_obj_type == 2) { // cpp
						m_class_path = std::string(m_script_path);
						m_pe_obj_type = pe::Object::ObjectType::CPP_OBJECT;
					}
					else { // none
						m_class_path = "";
						m_pe_obj_type = pe::Object::ObjectType::CPP_OBJECT;

					}
				}
				
				auto obj_tag = m_py_objmaker.attr("newObject")(std::string(m_obj_name), obj_id, std::string(m_script_name), m_obj_type, m_class_path,
					m_z_index, static_cast<bool>(m_visible), static_cast<bool>(m_persistance));

				m_py_objmaker.attr("writeObject")(obj_tag, obj_file_path);
				int error = CLI::getInstance()->projFileUpdate(false);
				if (error) { CLI::log("Error: in CLI::projFileUpdate(false) -> project file may damaged", Console::LOGLEVEL_ERROR); }
				FileTree::getInstance()->reload();
				m_popen = false;
			}

		}
		

		// render popups
		ExplorerPopup::getInstance()->render();

		if (ImGui::BeginPopupModal("Error!")) {
			ImGui::SetWindowSize(ImVec2(300, 120), ImGuiCond_Once);
			ImGui::Image(Resources::getOtherIcon("error")); ImGui::SameLine();
			if (m_obj_name[0] == '\0') ImGui::TextWrapped("Error! enter an Object Name!");
			else ImGui::TextWrapped("Error! enter the Object's Path!");
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
		if (ImGui::BeginPopupModal("Invalid Object Path!")) {
			ImGui::SetWindowSize(ImVec2(300, 120), ImGuiCond_Once);
			ImGui::Image(Resources::getOtherIcon("error")); ImGui::SameLine();
			ImGui::TextWrapped("Error! object path is invalid");
			if (ImGui::Button("OK", ImVec2(280, 20))) {
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
		if (ImGui::BeginPopupModal("Invalid Object Name!")) {
			ImGui::SetWindowSize(ImVec2(300, 140), ImGuiCond_Once);
			ImGui::Image(Resources::getOtherIcon("error")); ImGui::SameLine();
			ImGui::TextWrapped("Error! object name is invalid. (object name must start with alphabatic character and doesn't contain any of the following \\ / : * ? \" < > | spacebar)");
			if (ImGui::Button("OK", ImVec2(280, 20))) {
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}


		// capture selected path to inputs
		if (ExplorerPopup::getInstance()->isPathSelected() && ExplorerPopup::getInstance()->getParentWindow() == 1 ) {
			ExplorerPopup::getInstance()->setParentWindow(-1);
			auto rel_path = PyUtils::getInstance()->getFileUtil().attr("relPath")(ExplorerPopup::getInstance()->getSelectedPath()).cast<std::string>();
			const char* c; 
			int i = 0; // to copy string
			if (m_path_dst_ind == 0) {
				auto dir_name = PyUtils::getInstance()->getFileUtil().attr("getRelDirName")(rel_path).cast<std::string>();
				c = dir_name.c_str(); i = 0;
				while (c[i])  m_obj_path[i] = c[i++]; m_obj_path[i] = 0;
			}
			else if (m_path_dst_ind == 1) {
				
				if (py::str(rel_path).attr("endswith")(".py").cast<bool>()) { // path is pyton
					auto dir_name = PyUtils::getInstance()->getFileUtil().attr("getRelDirName")(rel_path).cast<std::string>();
					auto script_name = PyUtils::getInstance()->getOs().attr("path").attr("basename")(rel_path)
						.attr("split")(".").attr("__getitem__")(0).cast<std::string>();
					c = dir_name.c_str(); i = 0;
					while (c[i])  m_script_path[i] = c[i++]; m_script_path[i] = 0;
					c = script_name.c_str(); i = 0;
					while (c[i])  m_script_name[i] = c[i++]; m_script_name[i] = 0;
				}
				else {
					c = rel_path.c_str(); i = 0;
					while (c[i])  m_script_path[i] = c[i++]; m_script_path[i] = 0;
				}
					
				// set script path to input area
			}

			// guess path
			if (PyUtils::getInstance()->getStrUtil().attr("endswith")(std::string(m_script_path), std::string(".h")).cast<bool>()
				|| PyUtils::getInstance()->getStrUtil().attr("endswith")(std::string(m_script_path), std::string(".hpp")).cast<bool>())
			{
				m_obj_type = obj_type = 2; // cpp obj
			}
			ExplorerPopup::getInstance()->setPathSelectedFalse();
		}

		if (ScriptCreator::getInstance()->m_is_script_created && ScriptCreator::getInstance()->getParentWindow() == 0) {
			ScriptCreator::getInstance()->m_is_script_created = false;
			ScriptCreator::getInstance()->setParentWindow(-1);
			auto _scr_path = std::string(ScriptCreator::getInstance()->m_script_name);
			auto _scr_name = std::string(ScriptCreator::getInstance()->m_script_name);

			auto& c = ScriptCreator::getInstance()->m_script_path_name;
			int i = 0;
			while (c.c_str()[i])  m_script_path[i] = c.c_str()[i++]; m_script_path[i] = 0;
			i = 0;
			while (ScriptCreator::getInstance()->m_script_name[i])  m_script_name[i] = ScriptCreator::getInstance()->m_script_name[i++]; m_script_name[i] = 0;
		}

		ImGui::End();
	}
}