#include "pch.h"
#include "ScenePropEditor.h"

#include "utils/sfml_utils.h"


ScenePropEditor* ScenePropEditor::s_instance = nullptr;
sf::Color ScenePropEditor::s_color_axis = sf::Color(100, 100, 100);
sf::Color ScenePropEditor::s_color_scene_area = sf::Color(180, 180, 180);
int ScenePropEditor::s_scene_height_offset = 65;

void ScenePropEditor::handleEvent(sf::Event& event) {
	if (m_is_focus) {

		// scene move
		static sf::Vector2f mouse_ini_pos;
		static sf::Vector2f scene_ini_pos;
		if (event.type == sf::Event::EventType::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Middle) {
				mouse_ini_pos = m_mouse_pos;
				scene_ini_pos = m_scene_trans.getPosition();
			}
		}
		if (event.type == sf::Event::EventType::MouseMoved) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
				m_scene_trans.setPosition(-mouse_ini_pos + m_mouse_pos + scene_ini_pos);
				m_render_texture.clear( CLI::getInstance()->getPeproj().default_bg_color );
				// TODO: draw everything after the clear
			}
		}

		// scene zoom
		if (event.type == sf::Event::EventType::MouseWheelMoved) {
			if (event.mouseWheel.delta > 0) m_scene_trans.scale(1.1f, 1.1f);
			else if (m_scene_trans.getScale().x > .1) m_scene_trans.scale(.9f, .9f);
		}

		// resize render texture
		if (event.type == sf::Event::EventType::MouseButtonReleased) {
			if (event.mouseButton.button == sf::Mouse::Button::Left && m_window_size_changed){
				m_window_size_changed = false;
				m_render_texture.create(static_cast<unsigned int>(m_window_size.x), static_cast<unsigned int>(m_window_size.y - s_scene_height_offset));
			}
		}
	}
}


void ScenePropEditor::reloadScene(bool reload_file) {
	if (reload_file) m_scene_tag->attr("reload")();
	//CLI::getInstance()->getPeproj().window_size;
	// TODO: create scene
}

void ScenePropEditor::render() {
	m_is_focus = false;
	if (m_open) {
		ImGui::SetNextWindowSize(ImVec2(600, 400), ImGuiCond_Once);
		ImGui::Begin("Scene Editor", &m_open);
		if (ImGui::IsWindowFocused()) m_is_focus = true;
		m_mouse_pos = sf::Vector2f(ImGui::GetMousePos().x - ImGui::GetCursorScreenPos().x, ImGui::GetMousePos().y - ImGui::GetCursorScreenPos().y);
		
		// window size changed
		if (ImGui::GetWindowSize().x != m_window_size.x || ImGui::GetWindowSize().y != m_window_size.y) {
			m_window_size = ImGui::GetWindowSize();
			m_window_size_changed = true;
		}

		m_render_texture.clear(CLI::getInstance()->getPeproj().default_bg_color);
		drawAxisLines();

		// TODO: draw everyting
		static sf::Sprite spr;

		// apply trans
		auto rect = spr.getTextureRect();
		sf::RectangleShape r(sf::Vector2f(rect.width, rect.height));
		r.setFillColor(sf::Color(0, 0, 0, 0));
		r.setOutlineColor(sf::Color::Blue);
		r.setOutlineThickness(2.f/ m_scene_trans.getScale().x );

		spr.setPosition( m_scene_trans.getPosition());
		spr.setScale( m_scene_trans.getScale() );
		r.setPosition(m_scene_trans.getPosition());
		r.setScale(m_scene_trans.getScale());

		// mouse select
		if (
			r.getGlobalBounds().left   < m_mouse_pos.x &&
			r.getGlobalBounds().top    < m_mouse_pos.y &&
			r.getGlobalBounds().width + r.getGlobalBounds().left > m_mouse_pos.x&&
			r.getGlobalBounds().height + r.getGlobalBounds().top  > m_mouse_pos.y
			) {
			r.setOutlineColor(sf::Color::Yellow);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
				static sf::Vector2f mouse_ini_pos;
				static sf::Vector2f image_ini_pos;
			}
		}

		m_render_texture.draw( spr );
		m_render_texture.draw(r);
		spr.setTexture(Resources::getFileFormatIcon("file_cpp"));

		// test end

		ImGui::Image(m_render_texture);

		ImGui::Separator();
		
		// reset view
		if (ImGui::Button("reset view")) {
			m_scene_trans.setScale(1,1);
			m_scene_trans.setPosition(100,100);
		}

		ImGui::End();
	}
}

/*************************** private methods *************************************/

void ScenePropEditor::drawAxisLines() {
	pe::drawVertexLine(m_render_texture, sf::Vector2f(0, m_scene_trans.getPosition().y), sf::Vector2f(m_window_size.x, m_scene_trans.getPosition().y), s_color_axis);
	pe::drawVertexLine(m_render_texture, sf::Vector2f(m_scene_trans.getPosition().x, 0), sf::Vector2f(m_scene_trans.getPosition().x, m_window_size.y), s_color_axis);
	sf::Vector2f transformed_scene_size = static_cast<sf::Vector2f>(CLI::getInstance()->getPeproj().window_size);
	transformed_scene_size.x *= m_scene_trans.getScale().x;
	transformed_scene_size.y *= m_scene_trans.getScale().y;
	pe::drawVertexBox(m_render_texture, m_scene_trans.getPosition(), transformed_scene_size, s_color_scene_area);
}