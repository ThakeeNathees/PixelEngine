#include "pch.h"
#include "pyutils/PyUtils.h"
#include "ObjectCreator.h"
#include "ScriptsCreator.h"

ObjectCreater* ObjectCreater::s_instance;

void ObjectCreater::render()
{
	if (m_popen) {
		ImGui::Begin("Create New Object", &m_popen);
		ImGui::SetWindowSize(ImVec2(400, 320), ImGuiCond_Once);

		static float witdh_frac = .6;
		
		// start title
		ImGui::Text("Create a new Object Here"); ImGui::Text("");

		// object name
		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * witdh_frac);
		ImGui::InputText("obj_name", m_obj_name, sizeof(m_obj_name));

		// object path select
		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * witdh_frac);
		if (ImGui::InputText("obj_path   ", m_obj_path, sizeof(m_obj_path))) {
		}
		ImGui::SameLine();
		static auto obj_path_button = Resources::getFileFormatIcon("dir_open");
		if (ImGui::ImageButton(obj_path_button)) {
			m_path_dst_ind = 0;
			ExplorerPopup::getInstance()->setPath(".");
			ImGui::OpenPopup("Explorer");
		}

		// script path select
		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * witdh_frac);
		ImGui::InputText("scirpt_path", m_script_path, sizeof(m_script_path));
		ImGui::SameLine();
		static auto script_path_button = Resources::getFileFormatIcon("dir_open");
		if (ImGui::ImageButton(script_path_button)) {
			m_path_dst_ind = 1;
			ExplorerPopup::getInstance()->setPath(".");
			ImGui::OpenPopup("Explorer");
		}
		ImGui::SameLine();
		if (ImGui::ImageButton(Resources::getOtherIcon("create_new"))) {
			ScriptCreator::getInstance()->m_is_script_created = false;
			ScriptCreator::getInstance()->open();
		}
		if (ImGui::IsItemHovered()) ImGui::SetTooltip("create a new script");
		
		// class name
		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * witdh_frac);
		ImGui::InputText("class_name", m_class_name, sizeof(m_class_name));

		// class type
		const char* _obj_types[] = { "UNKNOWN","PYTHON_OBJECT", "CPP_OBJECT" };
		static int obj_type = 0;
		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * witdh_frac);
		if (ImGui::Combo("class_type", &obj_type, _obj_types, (int)(sizeof(_obj_types) / sizeof(const char*)))) {
			m_obj_type = obj_type;
		}
		
		// zindex, visible, persistence
		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * witdh_frac);
		ImGui::InputInt("z index", &m_z_index);

		const char* _bool[] = { "false","true"};
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
			else if (str_scr_path != std::string("") && !PyUtils::getInstance()->getFileUtil().attr("isPathScript")(str_scr_path).cast<bool>())
				ImGui::OpenPopup("Invalid Script Path!");
			else {
				m_object = pe::Assets::newObject();
				
				m_object->setName(m_obj_name);
				m_object->setVisible(m_visible);
				m_object->setZindex(m_z_index);
				m_object->setPersistence(m_persistance);
				if (m_script_path[0]) {
					m_object->__setClassName(m_class_name);
					switch (m_obj_type) {
						case 1: 
							m_object->__setObjectType(pe::Object::ObjectType::PYTHON_OBJECT); 
							m_object->__setClassPath( PyUtils::getInstance()->getFileUtil().attr("relPyObjDirPath") (m_script_path).cast<std::string>() );
							break;
						case 2: 
							m_object->__setObjectType(pe::Object::ObjectType::CPP_OBJECT); 
							m_object->__setClassPath(m_script_path);
							break;
						default: 
							m_object->__setObjectType(pe::Object::ObjectType::PYTHON_OBJECT); 
							break;
					}	
				}

				auto obj_tag = m_py_objmaker.attr("newObject")(m_object->getName(), m_object->getId(), m_object->getClassName(), m_obj_type, m_object->getClassPath(),
					m_object->getZindex(), m_object->isVisible(), m_object->isPersistence());
				m_py_objmaker.attr("writeObject")(obj_tag, m_obj_path);
				CLI::getInstance()->projUpdate(false);
				FileTree::getInstance()->reload();
				m_popen = false;
				// end and return;
			}

		}
		

		// render popups
		if (m_path_dst_ind==0) ExplorerPopup::getInstance()->render();
		else if (m_path_dst_ind==1) ExplorerPopup::getInstance()->render(false);

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
			ImGui::TextWrapped("Error! script path is invalid only supported for *.py, *.h, *.hpp");
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
		if (ExplorerPopup::getInstance()->isPathSelected()) {
			auto rel_path = PyUtils::getInstance()->getFileUtil().attr("relPath")(ExplorerPopup::getInstance()->getSelectedPath()).cast<std::string>();
			const char* c = rel_path.c_str();
			int i = 0; // to copy string
			if (m_path_dst_ind == 0) {
				while (c[i])  m_obj_path[i] = c[i++]; m_obj_path[i] = 0;
			}
			else if (m_path_dst_ind == 1) {
				// set script path to input area
				while (c[i])  m_script_path[i] = c[i++]; m_script_path[i] = 0;
			}
			ExplorerPopup::getInstance()->setPathSelectedFalse();
		}

		if (ScriptCreator::getInstance()->m_is_script_created) {
			ScriptCreator::getInstance()->m_is_script_created = false;
			auto _scr_path = std::string(ScriptCreator::getInstance()->m_script_name);
			auto _scr_name = std::string(ScriptCreator::getInstance()->m_script_name);

			auto& c = ScriptCreator::getInstance()->m_script_path_name;
			int i = 0;
			while (c.c_str()[i])  m_script_path[i] = c.c_str()[i++]; m_script_path[i] = 0;
			i = 0;
			while (ScriptCreator::getInstance()->m_script_name[i])  m_class_name[i] = ScriptCreator::getInstance()->m_script_name[i++]; m_class_name[i] = 0;
		}

		// find class name and type
		if (m_script_path[0] != '\0') {

			if (PyUtils::getInstance()->getStrUtil().attr("endswith")(std::string(m_script_path), std::string(".py")).cast<bool>()) {
				m_obj_type = obj_type = 1; // python obj

				// if type python class_name cant be changed (it's file name of path *.py)
				std::string _class_name = PyUtils::getInstance()->getFileUtil().attr("getPyFileName")(std::string(m_script_path)).cast<std::string>();
				int i = 0;
				while (_class_name.c_str()[i])  m_class_name[i] = _class_name.c_str()[i++]; m_class_name[i] = 0;
			}
			else if (PyUtils::getInstance()->getStrUtil().attr("endswith")(std::string(m_script_path), std::string(".h")).cast<bool>()
				|| PyUtils::getInstance()->getStrUtil().attr("endswith")(std::string(m_script_path), std::string(".hpp")).cast<bool>())
			{
				m_obj_type = obj_type = 2; // cpp obj
			}
			else {
				m_obj_type = obj_type = 0; // unknown obj
			}


		}
		//str_scr_path

		ImGui::End();
	}
}