#include "pch.h"
#include "ObjPropEditor.h"

// cpp include

#include "core/Resources.h"
#include "windows/ExplorerPopup.h"
#include "windows/assets_create/ScriptsCreator.h"

#include "windows/projerty_editor/SpritePropEditor.h"
#include "windows/projerty_editor/AreaPropEditor.h"

ObjPropEditor* ObjPropEditor::s_instance = nullptr;
int ObjPropEditor::s_tex_size = 100; 

void ObjPropEditor::render() {

	static float witdh_frac_indent = .4f;
	static float witdh_frac = .7f;

	if (m_open) {

		ImGui::SetNextWindowSize(ImVec2(600, 800), ImGuiCond_Once);
		ImGui::Begin("Object Property Editor", &m_open);

		static float pos_x = 0, pos_y = 0;
		static float rot = 0;
		static float scale_x = 0, scale_y = 0;
		static float origin_x = 0, origin_y = 0;

		if (ImGui::Button("Apply")) {
			if (m_obj_tag) {
				m_obj_tag->attr("save")();
				CLI::log(std::string("file saved: ").append(m_obj_tag->attr("getPath")().cast<std::string>()));
			}
		}
		ImGui::SameLine();
		if(ImGui::Button("clear")){
			m_obj_tag = nullptr;
			m_sprite = pe::Sprite();
			m_obj_name[0] = '\0';
			m_script_name[0] = '\0';
			m_script_path[0] = '\0';
			m_obj_type = 0;
			m_z_index = 0;
			m_visible = 1;
			m_persistance = 0;
			pos_x = 0; pos_y = 0;
			rot = 0;
			scale_x = 0; scale_y = 0;
			origin_x = 0; origin_y = 0;
		}

		ImGui::Separator();
		////////////////////////////////

		ImGui::BeginGroup();
		m_render_texture.draw(Resources::PNG_BG_SPRITE);
		m_render_texture.draw(m_sprite);
		ImGui::Image(m_render_texture);
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * witdh_frac_indent);
		if (ImGui::InputText("object name", m_obj_name, sizeof(m_obj_name))) { if (m_obj_tag) m_obj_tag->attr("setName")(std::string(m_obj_name)); }

		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * witdh_frac_indent);
		if (ImGui::InputText("script path", m_script_path, sizeof(m_script_path))) { if (m_obj_tag) m_obj_tag->attr("setScriptPath")(std::string(m_script_path)); }
		ImGui::SameLine();
		static auto script_path_button = Resources::getFileFormatIcon("dir_open");
		if (ImGui::ImageButton(script_path_button)) {
			m_path_dst_ind = 0;
			ExplorerPopup::getInstance()->setPath(".");
			ImGui::OpenPopup("Explorer");
			ExplorerPopup::getInstance()->setParentWindow(3);
		}
		ImGui::SameLine();
		if (ImGui::ImageButton(Resources::getOtherIcon("create_new"))) {
			ScriptCreator::getInstance()->setParentWindow(1);
			ScriptCreator::getInstance()->open();
		}
		if (ImGui::IsItemHovered()) ImGui::SetTooltip("create a new script");

		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * witdh_frac_indent);
		if (ImGui::InputText("script name", m_script_name, sizeof(m_script_name))) { if (m_obj_tag) m_obj_tag->attr("setScriptName")(std::string(m_script_name)); }
		// object type
		static const char* _obj_types[] = { "UNKNOWN", "PYTHON_OBJECT", "CPP_OBJECT" };
		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * witdh_frac_indent);
		if (ImGui::Combo("object type", &m_obj_type, _obj_types, (int)(sizeof(_obj_types) / sizeof(const char*)))) {
			m_obj_type = m_obj_type;
			if (m_obj_tag) {
				if (m_obj_type == 0 || m_obj_type == 2) m_obj_tag->attr("setObjectType")("CPP_OBJECT");
				else m_obj_tag->attr("setObjectType")("PYTHON_OBJECT");
			}
		}
		ImGui::EndGroup();

		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * witdh_frac);
		if (ImGui::InputInt("z index", &m_z_index)) { if (m_obj_tag)m_obj_tag->attr("setZindex")(m_z_index); }
		static const char* _bool[] = { "false","true" };
		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * witdh_frac);
		if (ImGui::Combo("visible", &m_visible, _bool, (int)(sizeof(_bool) / sizeof(const char*)))) {
			if (m_obj_tag) {
				if (m_visible) m_obj_tag->attr("setVisible")(true);
				else m_obj_tag->attr("setVisible")(false);
			}
		}
		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * witdh_frac);
		if (ImGui::Combo("persistence", &m_persistance, _bool, (int)(sizeof(_bool) / sizeof(const char*)))) {
			if (m_obj_tag) {
				if (m_persistance) m_obj_tag->attr("setPersistence")(true);
				else m_obj_tag->attr("setPersistence")(false);
			}
		}

		ImGui::Text("position");
		if (m_obj_tag) {
			auto pos = m_obj_tag->attr("getPosition")().cast<std::vector<float>>();
			pos_x = pos[0]; pos_y = pos[1];
		}
		ImGui::SameLine();
		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * witdh_frac/4);
		if (ImGui::InputFloat("posx", &pos_x) && m_obj_tag) {
			auto pos = m_obj_tag->attr("setPosition")(pos_x, pos_y);
		} ImGui::SameLine();
		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * witdh_frac/4);
		if (ImGui::InputFloat("posy", &pos_y) && m_obj_tag) {
			auto pos = m_obj_tag->attr("setPosition")(pos_x, pos_y);
		} 

		
		ImGui::Text("rotation"); ImGui::SameLine();
		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * witdh_frac/2);
		if (m_obj_tag) rot = m_obj_tag->attr("getRotation")().cast<float>();
		if (ImGui::InputFloat("angle", &rot) && m_obj_tag) {
			m_obj_tag->attr("setRotation")(rot);
		}

		ImGui::Text("scale   ");
		if (m_obj_tag) {
			auto scale = m_obj_tag->attr("getScale")().cast<std::vector<float>>();
			scale_x = scale[0]; scale_y = scale[1];
		}
		ImGui::SameLine();
		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * witdh_frac / 4);
		if (ImGui::InputFloat("sclx", &scale_x) && m_obj_tag) {
			auto pos = m_obj_tag->attr("setScale")(scale_x, scale_y);
		} ImGui::SameLine();
		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * witdh_frac / 4);
		if (ImGui::InputFloat("scly", &scale_y) && m_obj_tag) {
			auto pos = m_obj_tag->attr("setScale")(scale_x, scale_y);
		}

		ImGui::Text("origin  ");
		if (m_obj_tag) {
			auto origin = m_obj_tag->attr("getOrigin")().cast<std::vector<float>>();
			origin_x = origin[0]; scale_y = origin[1];
		}
		ImGui::SameLine();
		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * witdh_frac / 4);
		if (ImGui::InputFloat("orgx", &origin_x) && m_obj_tag) {
			auto pos = m_obj_tag->attr("setOrigin")(origin_x, origin_y);
		} ImGui::SameLine();
		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * witdh_frac / 4);
		if (ImGui::InputFloat("orgy", &origin_y) && m_obj_tag) {
			auto pos = m_obj_tag->attr("setOrigin")(origin_x, origin_y);
		}

		if (m_obj_tag) {
			// sprite button
			if (m_obj_tag->attr("hasSpriteTag")().cast<bool>()) {
				if (ImGui::ImageButton(Resources::getOtherIcon("sprite"))) {
					SpritePropEditor::getInstance()->open(m_obj_tag);
				}
			}
			else {
				if (ImGui::ImageButton(Resources::getOtherIcon("new_sprite"))) {
					int spr_id = CLI::getInstance()->getPeproj().next_sprite_id++;
					m_obj_tag->attr("createSprite")(spr_id);
					m_obj_tag->attr("save")();
					SpritePropEditor::getInstance()->open(m_obj_tag);
				}
			}

			ImGui::SameLine();
			// area button
			if (m_obj_tag->attr("hasAreaTag")().cast<bool>()) {
				if (ImGui::ImageButton(Resources::getOtherIcon("area"))) {
					AreaPropEditor::getInstance()->open(m_obj_tag);
				}
			}
			else {
				if (ImGui::ImageButton(Resources::getOtherIcon("new_area"))) {
					int spr_id = CLI::getInstance()->getPeproj().next_area_id++;
					m_obj_tag->attr("createArea")(spr_id);
					m_obj_tag->attr("save")();
					AreaPropEditor::getInstance()->open(m_obj_tag);
				}
			}
		}
		else {
			ImGui::ImageButton(Resources::getOtherIcon("new_sprite"));
			ImGui::SameLine();
			ImGui::ImageButton(Resources::getOtherIcon("new_area"));

		}




		/*******************************************************/


		// render popups
		ExplorerPopup::getInstance()->render();


		// capture selected path to inputs
		if (ExplorerPopup::getInstance()->isPathSelected() && ExplorerPopup::getInstance()->getParentWindow() == 3) {
			ExplorerPopup::getInstance()->setParentWindow(-1);

			auto rel_path = PyUtils::getInstance()->getFileUtil().attr("relPath")(ExplorerPopup::getInstance()->getSelectedPath()).cast<std::string>();
			const char* c;
			int i = 0; // to copy string

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
			ExplorerPopup::getInstance()->setPathSelectedFalse();
		}

		// capture created script path
		if (ScriptCreator::getInstance()->m_is_script_created && ScriptCreator::getInstance()->getParentWindow() == 1) {
			ScriptCreator::getInstance()->m_is_script_created = false;
			ScriptCreator::getInstance()->setParentWindow(-1);
			auto _scr_path = std::string(ScriptCreator::getInstance()->m_script_path);
			auto _scr_name = std::string(ScriptCreator::getInstance()->m_script_name);
			auto _file_path = ScriptCreator::getInstance()->m_script_path_name;
			_scr_path = PyUtils::getInstance()->getFileUtil().attr("relPath")(_scr_path).cast<std::string>();

			int i = 0;
			const char* c;
			if (py::str(_file_path).attr("endswith")(".py").cast<bool>()) { // path is pyton
				c = _scr_path.c_str(); i = 0;
				while (c[i])  m_script_path[i] = c[i++]; m_script_path[i] = 0;
				c = _scr_name.c_str(); i = 0;
				while (c[i])  m_script_name[i] = c[i++]; m_script_name[i] = 0;
			}
			else {
				c = _scr_path.c_str(); i = 0;
				while (c[i])  m_script_path[i] = c[i++]; m_script_path[i] = 0;
			}
		}


		ImGui::End();
	}
} // render end