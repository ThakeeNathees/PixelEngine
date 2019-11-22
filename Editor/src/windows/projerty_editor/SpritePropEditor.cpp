#include "pch.h"
#include "SpritePropEditor.h"

#include "core/CLI.h"
#include "ObjPropEditor.h"

SpritePropEditor* SpritePropEditor::s_instance = nullptr;
int SpritePropEditor::s_tex_size = 200;

void SpritePropEditor::reloadSprite(bool reload_file) {
	if (reload_file) m_obj_tag->attr("reload")();
	if (m_obj_tag->attr("hasSpriteTag")().cast<bool>()) {
		int tex_id = m_obj_tag->attr("getSpriteTextureId")().cast<int>();
		if (tex_id >= 0) {
			m_sprite.setTexture(*pe::Assets::getAsset<pe::Texture>(tex_id), true);
			//auto rect = m_obj_tag->attr("getSpriteTextureRect")().cast<std::vector<int>>();
			//m_sprite.setTextureRect(sf::IntRect(rect[0], rect[1], rect[2], rect[3]));
			auto frames = m_obj_tag->attr("getSpriteFrames")().cast<std::vector<int>>();
			x = frames[0]; y = frames[1]; offset_x = frames[2]; offset_y = frames[3]; ind = frames[4];
			m_sprite.setFrames(frames[0], frames[1], frames[2], frames[3]);
			m_sprite.setFrameIndex(frames[4]);
		}
		else {
			auto texture = pe::Texture();
			m_sprite.setTexture(texture, true);
		}
		bool is_height_min = (m_sprite.getTextureRect().width > m_sprite.getTextureRect().height);
		int spr_size = std::max(m_sprite.getTextureRect().width, m_sprite.getTextureRect().height);
		m_sprite.setScale(s_tex_size / (float)spr_size, s_tex_size / (float)spr_size);
		if (is_height_min) m_sprite.setPosition(0, (s_tex_size - m_sprite.getScale().x * m_sprite.getTextureRect().height) / 2);
		else m_sprite.setPosition((s_tex_size - m_sprite.getScale().x * m_sprite.getTextureRect().width) / 2, 0);
	}
	else {
		m_sprite = pe::Sprite();
	}
}


void SpritePropEditor::render() {
	static float witdh_frac = .4f;

	if (m_open) {
		ImGui::SetNextWindowSize(ImVec2(600, s_tex_size + 40), ImGuiCond_Once);
		ImGui::Begin("Sprite Property Editor", &m_open);

		ImGui::BeginGroup();
		m_render_texture.draw(Resources::PNG_BG_SPRITE);
		m_render_texture.draw(m_sprite);
		ImGui::Image(m_render_texture);
		ImGui::EndGroup();

		ImGui::SameLine();
		ImGui::BeginGroup();
		auto texs = pe::Assets::getTextures();
		const char** tex_names = new const char*[texs.size()+1];
		tex_names[0] = "None";
		for (int i = 1; i < texs.size()+1; i++) {
			tex_names[i] = pe::Assets::getAsset<pe::Texture>(texs[i-1])->getName().c_str();
		}
		if (m_ind > texs.size()) m_ind = 0;
		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * witdh_frac);
		if (ImGui::Combo("texture name", &m_ind, tex_names, texs.size()+1 )) {
			if (m_obj_tag) {
				if (m_ind == 0)m_obj_tag->attr("setSpriteTextureId")(-1);
				else m_obj_tag->attr("setSpriteTextureId")(texs[m_ind - 1]);
				reloadSprite();
			}
		}
		delete[] tex_names;

		ImGui::Text("frames");
		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * witdh_frac/2);
		if (ImGui::InputInt("x       ", &x) && m_obj_tag) {
			if (x < 1) x = 1; if (ind >= x * y) ind = 0;
			m_obj_tag->attr("setSpriteFrames")(x, y, offset_x, offset_y, ind);
			reloadSprite();
		} ImGui::SameLine();
		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * witdh_frac/2);
		if (ImGui::InputInt("y       ", &y) && m_obj_tag) {
			if (y < 1) y = 1; if (ind >= x * y) ind = 0;
			m_obj_tag->attr("setSpriteFrames")(x, y, offset_x, offset_y, ind);
			reloadSprite();
		}
		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * witdh_frac/2);
		if (ImGui::InputInt("offset_x", &offset_x) && m_obj_tag) {
			if (offset_x < 0) offset_x = 0;
			m_obj_tag->attr("setSpriteFrames")(x, y, offset_x, offset_y, ind);
			reloadSprite();
		}ImGui::SameLine();
		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * witdh_frac/2);
		if (ImGui::InputInt("offset_y", &offset_y) && m_obj_tag) {
			if (offset_y < 0) offset_y = 0;
			m_obj_tag->attr("setSpriteFrames")(x, y, offset_x, offset_y, ind);
			reloadSprite();
		}
		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * witdh_frac);
		if (ImGui::InputInt("index", &ind) && m_obj_tag) {
			if (ind < 0 ) ind = 0;
			if (ind >= x * y) ind = 0;
			m_obj_tag->attr("setSpriteFrames")(x, y, offset_x, offset_y, ind);
			reloadSprite();
		}
		
		if (ImGui::Button("Apply")){
			if (m_obj_tag) {
				m_obj_tag->attr("save")();
				CLI::log(std::string("file saved: ").append(m_obj_tag->attr("getPath")().cast<std::string>()));
				if (ObjPropEditor::getInstance()->getObjTag() == m_obj_tag) {
					ObjPropEditor::getInstance()->reloadObj();
				}
				m_open = false;
			}
		}

		ImGui::EndGroup();

		ImGui::End();
	}
}