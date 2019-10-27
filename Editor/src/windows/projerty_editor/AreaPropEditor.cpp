#include "pch.h"
#include "AreaPropEditor.h"

AreaPropEditor* AreaPropEditor::s_instance;
int AreaPropEditor::s_tex_size = 400;
int AreaPropEditor::s_tex_margin = 20;
sf::Color AreaPropEditor::s_area_color = sf::Color(50, 75, 100, 180);


void AreaPropEditor::reloadSprite(bool reload_file) {
	if (reload_file) m_obj_tag->attr("reload")();
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
		if (spr_size == 0)spr_size = 100 ;
		m_sprite.setScale(s_tex_size / (float)spr_size, s_tex_size / (float)spr_size);
		if (is_height_min) m_sprite.setPosition(0, (s_tex_size - m_sprite.getScale().x * m_sprite.getTextureRect().height) / 2);
		else m_sprite.setPosition((s_tex_size - m_sprite.getScale().x * m_sprite.getTextureRect().width) / 2 + s_tex_margin / 2.f, s_tex_margin / 2.f);
	}
	else {
		m_sprite = pe::Sprite();
		m_sprite.setTextureRect(sf::IntRect(0,0,s_tex_size-s_tex_margin, s_tex_size-s_tex_margin));
		m_sprite.setPosition(s_tex_margin / 2.f, s_tex_margin / 2.f);
	}
}

void AreaPropEditor::reloadArea(bool reload_file) {
	if (reload_file) m_obj_tag->attr("reload")();
	if (m_obj_tag && m_obj_tag->attr("hasAreaTag")().cast<bool>()) {
		auto points = m_obj_tag->attr("getAreaPoints")().cast<std::vector<std::vector<float>>>();

		m_area = sf::ConvexShape(points.size());
		m_points.clear();
		for (int i = 0; i < points.size(); i++) {
			auto pos = m_sprite.getTransform().transformPoint(sf::Vector2f((float)points[i][1], (float)points[i][2]));
			m_area.setPoint((int)points[i][0], pos);

			static float radious = 5;
			sf::CircleShape point(radious);
			point.setOrigin(radious, radious);
			point.setPosition(pos.x, pos.y);
			point.setFillColor(sf::Color(sf::Color::Magenta));
			m_points[(int)points[i][0]] = point;
		}

		m_area.setOutlineColor(sf::Color::Black);
		m_area.setFillColor(s_area_color);
		m_area.setOutlineThickness(2);
	}
}

void AreaPropEditor::reloadObj(bool reload_file) {
	
	reloadSprite(reload_file);
	reloadArea();
}

void AreaPropEditor::render() {
	if (m_open) {
		ImGui::Begin("Area Property Editor", &m_open);

		// create new point
		if (ImGui::Button("Add Point") && m_selected_point < 0){
			if (m_obj_tag && m_obj_tag->attr("hasAreaTag")().cast<bool>()) {
				m_selected_point = m_obj_tag->attr("addAreaPoint")(10, 10).cast<int>();
				reloadArea();
			}
		}
		// remove point
		ImGui::SameLine();
		if (ImGui::Button("Remove Point")) {
			if (m_obj_tag) {
				m_obj_tag->attr("removeAreaPoint")();
				reloadArea();
			}
		}
		// clear points
		ImGui::SameLine();
		if (ImGui::Button("Clear")) {
			if (m_obj_tag) {
				m_obj_tag->attr("clearAreaPoints")();
				reloadArea();
			}
		}
		// reset points
		ImGui::SameLine();
		if (ImGui::Button("Reset")) {
			reloadArea(true);
		}
		// save
		ImGui::SameLine();
		if (ImGui::Button("Apply")) {
			if (m_obj_tag) {
				if (!pe::isShapeConvex(m_area) || m_area.getPointCount() < 3) {
					ImGui::OpenPopup("Invalid Shape");
				}
				else {
					m_obj_tag->attr("save")();
					m_open = false;
				}
			}
		}

		m_render_texture.draw(Resources::PNG_BG_SPRITE);
		m_render_texture.draw(m_sprite);
		m_render_texture.draw(m_area);
		

		/*******************************************************/

		// render points
		m_mouse_pos = sf::Vector2f(ImGui::GetMousePos().x - ImGui::GetCursorScreenPos().x, ImGui::GetMousePos().y - ImGui::GetCursorScreenPos().y);
		bool reload_area = false;
		for (auto& pair : m_points) {
			auto point = pair.second; int ind = pair.first;

			// point color
			bool any_point_hovered = false;
			auto r = point.getRadius(); auto pos = point.getPosition();
			if (m_mouse_pos.x < pos.x + r && pos.x - r < m_mouse_pos.x && m_mouse_pos.y < pos.y + r && pos.y - r < m_mouse_pos.y) {
				point.setFillColor(sf::Color::Yellow);
				m_hovered_point = ind;
				if (ImGui::IsMouseDown(0)) { m_selected_point = ind; }
				any_point_hovered = true;
			}
			else point.setFillColor(sf::Color::Magenta);
			
			bool mouse_on_render_area = 0 < m_mouse_pos.x && m_mouse_pos.x < m_render_texture.getSize().x &&
			0 < m_mouse_pos.y && m_mouse_pos.y < m_render_texture.getSize().y;
			if (ImGui::IsMouseReleased(0) && mouse_on_render_area) m_selected_point = -1;
			if (!any_point_hovered) m_hovered_point = -1;

			// point move
			if (m_selected_point >= 0 ) {
				m_points[m_selected_point].setPosition(m_mouse_pos);
				if (m_obj_tag) {
					auto trans_point = m_sprite.getInverseTransform().transformPoint(m_mouse_pos.x, m_mouse_pos.y);
					m_obj_tag->attr("setAreaPoint")(m_selected_point,  trans_point.x, trans_point.y );
					reload_area = true;
					if (pe::isShapeConvex(m_area)) {
						s_area_color = sf::Color(50, 75, 100, 180);
					}
					else {
						s_area_color = sf::Color(200, 75, 50, 180);
					}
				}
			}

			m_render_texture.draw(point);
		}


		ImGui::BeginChild("Image", m_render_texture.getSize(), false, ImGuiWindowFlags_NoMove);
		ImGui::Image(m_render_texture);
		ImGui::EndChild();
		if (reload_area) reloadArea();


		if (ImGui::BeginPopupModal("Invalid Shape")) {
			ImGui::SetWindowSize(ImVec2(300, 120), ImGuiCond_Once);
			ImGui::Image(Resources::getOtherIcon("error")); ImGui::SameLine();
			ImGui::TextWrapped("Error! Shape for the area is invalid. (the shape must be convex and contain at least 3 points)");
			if (ImGui::Button("OK", ImVec2(280, 20))) {
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}

		ImGui::End();

	}
}