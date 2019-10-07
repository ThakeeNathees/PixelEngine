#pragma once

#include "core/cli/CLI.h"

class ApplicationHolder
{
public:
	static bool s_reload_on_save;
private:
	static bool s_is_running;
	static bool s_is_focus;

	static std::string s_proj_file_name;
	static pe::Application* s_application;
	static sf::RenderTexture s_render_texture;
	ApplicationHolder() = delete;

	static sf::Vector2f s_mouse_pos;
	static sf::Vector2f s_mouse_rel_pos; // mouse position relative to window

public:

	static void setProjFileName(const std::string& file_name) {
		s_proj_file_name = file_name;
	}
	static pe::Application* getApplication() {
		return s_application;
	}
	static sf::RenderTexture& getRenderTexture() {
		return s_render_texture;
	}

	static bool isRunning() { return s_is_running && s_application != nullptr; }
	
	// for call from python with module peio
	static sf::Vector2f getMousePosition() { return s_mouse_pos; }
	static sf::Vector2f getMouseRelPosition() { return s_mouse_rel_pos; }
	static bool isWindowFocus() { return s_is_focus; }

	static void start() {
		reloadApplication();
		s_is_running = true;
	}
	static void stop() {
		s_is_running = false;
	}

	static void reloadApplication() {
		try {
			auto application = new pe::Application(s_proj_file_name.c_str(), false, &s_render_texture);
			if (s_application) delete s_application;
			s_application = application;
			s_render_texture.create(s_application->getWindowSize().x, s_application->getWindowSize().y);
			CLI::getInstance()->getConsole()->addLog("APPLICATION RELOAD SUCCESS!", 1);
		}
		catch (const std::exception& e){
			CLI::getInstance()->getConsole()->addLog(e.what(), 3);
		}

	}
	static void reloadScripts() {
		if (s_application) {
			s_application->reloadScritps();
			CLI::getInstance()->getConsole()->addLog("SCRIPTS RELOAD SUCCESS!", 1);
		}
	}

	static void render() {
		if (s_is_running) {
			ImGui::Begin("Applicaton window", &s_is_running);
			s_is_focus =  ImGui::IsRootWindowFocused();
			s_mouse_pos = sf::Vector2f(ImGui::GetMousePos().x - ImGui::GetCursorScreenPos().x, ImGui::GetMousePos().y - ImGui::GetCursorScreenPos().y);
			s_mouse_rel_pos = sf::Vector2f( ImGui::GetWindowPos().x, ImGui::GetWindowPos().y);
			ImGui::SetWindowSize( ImVec2(s_application->getWindowSize().x, s_application->getWindowSize().y), ImGuiCond_Appearing );

			ImGui::Image(ApplicationHolder::getRenderTexture());

			ImGui::End();
		}
	}

};