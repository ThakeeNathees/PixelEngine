#pragma once

class FontViewer
{

public:

	static FontViewer* getInstance() {
		if (s_instance == nullptr) s_instance = new FontViewer();
		return s_instance;
	}

	void handleEvent(sf::Event& event) {
		if (m_is_focus) {
			if (event.type == sf::Event::EventType::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Button::Left) {
					m_render_texture.create(static_cast<unsigned int>( m_window_size.x), static_cast<unsigned int>(m_window_size.y - 35));
					m_render_texture.clear();
					m_render_texture.draw(m_text);
				}
			}
		}
	}

	void openFontViwer(const std::string& path) {
		m_open = true;
		if (m_path == path) return;
		m_path = path;
		m_font.loadFromFile(path);
		m_render_texture.create(static_cast<unsigned int>(m_window_size.x), static_cast<unsigned int>(m_window_size.y - 35));
		m_text.setFont(m_font);
		m_render_texture.clear();
		m_render_texture.draw(m_text);
	}


	void render() {
		m_is_focus = false;
		if (m_open) {
			ImGui::Begin(m_path.c_str(), &m_open, ImGuiWindowFlags_NoScrollbar);
			ImGui::SetWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);
			m_window_size = ImGui::GetWindowSize();
			m_is_focus = ImGui::IsRootWindowFocused();
			ImGui::Image(m_render_texture);
			ImGui::End();
		}
		
	}

private:
	FontViewer() {

		m_text.setString(
			"Lorem  ipsum  dolor in  sit  amet,  consectetur\n"
			"adipiscing  non elit, sed  do   eiusmod  tempor\n"
			"incididunt  ut labore et dolore magna  a liqua.\n"
			"Ut   enim  ad  minim   veniam,  quis    nostrud\n"
			"exercitation  ullamco laboris nisi ut   aliquip\n"
			"ex ea commodo consequat. Duis aute irure  dolor\n"
			"in reprehenderit in voluptate velit esse cillum\n"
			"dolore eu fugiat nulla pariatur. Excepteur sint\n"
			"occaecat   cupidatat   non  proident,  sunt in \n"
			"culpa qui officia deserunt mollit anim laborum.\n"
			"\n"
			"Morbi  tristique senectus et netus et malesuada\n"
			"fames ac turpis. Proin sagittis  rhoncus mattis\n"
			"rhoncus  urna neque viverra. Elementum  integer\n"
			"enim neque volutpat ac tincidunt. Sagittis nisl\n"
			"rhoncus mattis rhoncus urna neque viverra justo\n"
			"Aliquam malesuada bibendum arcu vitae elementum\n"
			"curabitur.  Lacinia  quis  vel  eros  donec ac.\n"
			"Elementum integer enim neque volutpat tincidunt\n"
			"semper qui. Erat at lectus urna duis convallis.\n"
			"Adipiscing elit pellentesque habitant morbi tri\n"
			"senectus et. Mus mauris vitae ultricies integer\n"
			"malesuada nunc vel."
		);

	}

	static FontViewer* s_instance;
	sf::Text m_text;
	sf::Font m_font;
	sf::RenderTexture m_render_texture;

	ImVec2 m_window_size = ImVec2(800,600);

	std::string m_path;
	bool m_open = false;
	bool m_is_focus = false;



};