#pragma once

#include "core/cli/CLI.h"

class ApplicationHolder
{
public:
	static bool s_open;
	static bool s_reload_on_save;
	static bool* s_debug_mode;
private:
	static bool s_has_error;
	static bool s_is_running;
	static bool s_is_focus;
	static bool __s_is_application_reloaded;

	static std::string s_proj_file_name;
	static pe::Application* s_application;
	static sf::RenderTexture s_render_texture;
	static sf::RenderTexture s_default_texture; // TODO: draw pixel-engine logo
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
	
	static bool hasError() { return s_has_error; }
	static void setError(bool has_error) { s_has_error = has_error; }
	
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
			//s_debug_mode = s_application->_getDebugPtr();
			__s_is_application_reloaded = true;
			CLI::getInstance()->getConsole()->addLog("APPLICATION RELOAD SUCCESS!", 1);
			CLI::getInstance()->getConsole()->addLog("WARNING : RUNNING THE APPLICATION INSIDE THE ENGINE EDITOR MAY CAUSE THE FRAME RATE DROP!", 2);
		}
		catch (const std::exception& e){
			CLI::getInstance()->getConsole()->addLog(e.what(), 3);
		}

	}
	
	
	static void reloadScripts() {
		if (s_application) {
			try {
				s_application->reloadScritps();
				CLI::getInstance()->getConsole()->addLog("SCRIPTS RELOAD SUCCESS!", 1);
				s_has_error = false; // if has, checked and set true in main
			}
			catch (const std::exception& e){
				CLI::getInstance()->getConsole()->addLog(e.what(), 3);
				s_has_error = true;
			}
		}
	}

	static void render() {
		if (s_open) {
			if (s_is_running) {
				ImGui::Begin("Applicaton window", &s_open);
				s_is_focus = ImGui::IsRootWindowFocused();
				s_mouse_pos = sf::Vector2f(ImGui::GetMousePos().x - ImGui::GetCursorScreenPos().x, ImGui::GetMousePos().y - ImGui::GetCursorScreenPos().y);
				s_mouse_rel_pos = sf::Vector2f(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y);
				if (__s_is_application_reloaded) {
					__s_is_application_reloaded = false;
					ImGui::SetWindowSize(ImVec2(s_application->getWindowSize().x, s_application->getWindowSize().y + ImGui::GetFontSize() + 25));
				}
				ImGui::Image(ApplicationHolder::getRenderTexture());
				ImGui::End();
			}
			else {
				ImGui::Begin("Applicaton window", &s_open);
				ImGui::Image(s_default_texture);
				ImGui::End();
			}
		}
	}

};