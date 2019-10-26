#include "pch.h"
#include "AreaPropEditor.h"

AreaPropEditor* AreaPropEditor::s_instance;
int AreaPropEditor::s_tex_size = 400;
int AreaPropEditor::s_tex_margin = 20;


void AreaPropEditor::reloadObj(bool reload_file) {
	if (reload_file) m_obj_tag->attr("reload")();
	
	// sprite
	if (m_obj_tag->attr("hasSpriteTag")().cast<bool>()) {
		int tex_id = m_obj_tag->attr("getSpriteTextureId")().cast<int>();
		if (tex_id >= 0) {
			m_sprite.setTexture(*pe::Assets::getAsset<pe::Texture>(tex_id), true);
			auto frames = m_obj_tag->attr("getSpriteFrames")().cast<std::vector<int>>();
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
		else m_sprite.setPosition((s_tex_size - m_sprite.getScale().x * m_sprite.getTextureRect().width) / 2 + s_tex_margin/2, s_tex_margin/2);
	}
	else {
		m_sprite = pe::Sprite();
	}

	if (m_obj_tag && m_obj_tag->attr("hasAreaTag")().cast<bool>()) {
		auto points = m_obj_tag->attr("getAreaPoints")().cast<std::vector<std::vector<int>>>();

		m_area = sf::ConvexShape(points.size());
		for (int i = 0; i < points.size(); i++) {
			m_area.setPoint(points[i][0], m_sprite.getTransform().transformPoint(sf::Vector2f(points[i][1], points[i][2])));
		}

		m_area.setOutlineColor(sf::Color::Black);
		m_area.setFillColor(sf::Color(50, 75, 100, 180));
		m_area.setOutlineThickness(2);
	}
}

void AreaPropEditor::render() {
	if (m_open) {
		ImGui::Begin("Area Property Editor", &m_open);
		m_render_texture.draw(Resources::PNG_BG_SPRITE);
		m_render_texture.draw(m_sprite);
		m_render_texture.draw(m_area);
		ImGui::Image(m_render_texture);
		ImGui::End();
	}
}