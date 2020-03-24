#include "pch.h"
#include "core/EmbededApplication.h"

EmbeddedApplication* EmbeddedApplication::s_instance = nullptr;

void EmbeddedApplication::reloadApplication() {
	try {
		CLI::getInstance()->updatePeproj();
		
		try {
			auto application = new pe::Application(CLI::getInstance()->getProjFileName().c_str(), false, &m_render_texture);
			if (m_application) delete m_application;
			m_application = application;
			m_is_running = true;
			m_render_texture.create(m_application->getWindowSize().x, m_application->getWindowSize().y);
			m_is_application_reloaded = true;
			CLI::getInstance()->getConsole()->addLog("Application reload success!", Console::LOGLEVEL_SUCCESS);
			CLI::getInstance()->getConsole()->addLog("Warning: Running the application inside the engine editor may cause the frame rate drop!", Console::LOGLEVEL_WARNING);
		}
		catch (const std::exception& err){
			CLI::log(err.what(), Console::LOGLEVEL_ERROR);
		}
	}
	catch (const std::exception & e) {
		CLI::getInstance()->getConsole()->addLog(e.what(), Console::LOGLEVEL_ERROR);
	}

}

void EmbeddedApplication::reloadScripts() {
	if (m_application) {
		try {
			m_application->reloadScritps();
			CLI::getInstance()->getConsole()->addLog("SCRIPTS RELOAD SUCCESS!", 1);
			m_has_error = false; // if has, checked and set true in main
		}
		catch (const std::exception & e) {
			CLI::getInstance()->getConsole()->addLog(e.what(), 3);
			m_has_error = true;
		}
	}
}


void EmbeddedApplication::render() {
	if (m_open) {
		if (m_is_running) {
			ImGui::Begin("Applicaton window", &m_open);
			m_is_window_focus = ImGui::IsRootWindowFocused();
			m_mouse_pos = sf::Vector2f(ImGui::GetMousePos().x - ImGui::GetCursorScreenPos().x, ImGui::GetMousePos().y - ImGui::GetCursorScreenPos().y);
			if (m_is_application_reloaded) {
				m_is_application_reloaded = false;
				ImGui::SetWindowSize(ImVec2(
					static_cast<float>(m_application->getWindowSize().x), static_cast<float>(m_application->getWindowSize().y + ImGui::GetFontSize() + 25))
				);
			}
			ImGui::Image(m_render_texture);
			ImGui::End();
		}
		else {
			ImGui::Begin("Applicaton window", &m_open);
			static ImVec2 window_size = ImVec2(0, 0);
			if (ImGui::GetWindowSize().x != window_size.x || ImGui::GetWindowSize().y != window_size.y) {
				window_size = ImGui::GetWindowSize();
				m_default_texture.create(static_cast<unsigned int>(window_size.x), static_cast<unsigned int>(std::max(window_size.y - 35, 10.f)));
				m_default_texture.clear(sf::Color::White);

				sf::Sprite logo;
				logo.setTexture(Resources::LOGO_PE);
				logo.setScale(.2f, .2f);
				auto tex_size = logo.getTexture()->getSize();
				logo.setOrigin(static_cast<float>(tex_size.x / 2), static_cast<float>(tex_size.y / 2));
				logo.setPosition(window_size.x / 2, window_size.y / 2);

				m_default_texture.draw(logo);
			}
			ImGui::Image(m_default_texture);
			ImGui::End();
		}
	}
}