#pragma once


class ImageViwer
{

public:

	void handleEvent(sf::Event& event) {
		if (m_is_focus) {

			// image move
			static sf::Vector2f mouse_ini_pos;
			static sf::Vector2f image_ini_pos;
			if (event.type == sf::Event::EventType::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Middle) {
					mouse_ini_pos = m_mouse_pos;
					image_ini_pos = m_image.getPosition();
				}
			}
			if (event.type == sf::Event::EventType::MouseMoved) {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
					m_image.setPosition(-mouse_ini_pos + m_mouse_pos + image_ini_pos);
					m_render_texture.clear();
					m_render_texture.draw(Resources::PNG_BG_SPRITE);
					m_render_texture.draw(m_image);
				}
			}

			// scroll zoom
			if (event.type == sf::Event::EventType::MouseWheelMoved) {
				
				m_image.setOrigin(m_image.getInverseTransform().transformPoint(m_mouse_pos));
				m_image.setPosition(m_mouse_pos);

				if (event.mouseWheel.delta > 0) m_image.scale(1.1f, 1.1f);
				else if (m_image.getScale().x > .1) m_image.scale(.9f, .9f);
				
				m_render_texture.clear();
				m_render_texture.draw(Resources::PNG_BG_SPRITE);
				m_render_texture.draw(m_image);
			}

			// resize render texture
			if (event.type == sf::Event::EventType::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Button::Left) {
					m_render_texture.create(static_cast<unsigned int>(m_window_size.x), static_cast<unsigned int>(m_window_size.y - 35));
					m_render_texture.draw(Resources::PNG_BG_SPRITE);
					m_render_texture.draw(m_image);
				}
			}
		}
	}

	void openImageViwer(const std::string& path) {
		m_open = true;
		if (m_path == path) return;
		m_path = path;
		m_texture.loadFromFile(path);
		m_image.setTexture(m_texture, true);
		m_render_texture.create(
			static_cast<unsigned int>(m_window_size.x), static_cast<unsigned int>(m_window_size.y-35)
		);

		m_render_texture.draw(Resources::PNG_BG_SPRITE);
		m_render_texture.draw(m_image);
	}

	static ImageViwer* getInstance() {
		if (!s_instance) s_instance = new ImageViwer();
		return s_instance;
	}

	void render() {
		m_is_focus = false;
		if (m_open) {
			ImGui::Begin("ImageViwer", &m_open);
			ImGui::SetWindowSize(ImVec2(800, 600), ImGuiCond_Once);
			if (ImGui::IsRootWindowFocused()) m_is_focus = true;
			m_window_size = ImGui::GetWindowSize();
			m_mouse_pos = sf::Vector2f(ImGui::GetMousePos().x - ImGui::GetCursorScreenPos().x, ImGui::GetMousePos().y - ImGui::GetCursorScreenPos().y);

			ImGui::Image(m_render_texture);
			ImGui::End();
		}
	}



private:
	ImageViwer() {}
	std::string m_path;
	sf::Texture m_texture;
	sf::Sprite m_image;
	sf::RenderTexture m_render_texture;

	sf::Vector2f m_mouse_pos;

	ImVec2 m_window_size = ImVec2(800,600);

	bool m_open = false;
	bool m_is_focus = false;
	static ImageViwer* s_instance;

	
};