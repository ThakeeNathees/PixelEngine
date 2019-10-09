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
		pe::FileHandler file;
		int error = file.readProject(s_proj_file_name.c_str());
		if (error) { PE_LOG("project file reading error"); CLI::log("Error: reading project file was failure!",Console::LOGLEVEL_ERROR); }
		else { PE_LOG("project file reading success"); CLI::log("Project file has read");}
		auto proj = file.getProject();

		error = file.readAssets("assets.xml"); // TODO: name consistency
		if (error) { PE_LOG("assets file reading error"); CLI::log("Error: Assets reading failure!", Console::LOGLEVEL_ERROR); }
		else { PE_LOG("assets file reading success"); CLI::log("Assets loaded");}

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
			__s_is_application_reloaded = true;
			CLI::getInstance()->getConsole()->addLog("Application reload success!", Console::LOGLEVEL_SUCCESS);
			CLI::getInstance()->getConsole()->addLog("Warning: Running the application inside the engine editor may cause the frame rate drop!", Console::LOGLEVEL_WARNING);
		}
		catch (const std::exception& e){
			CLI::getInstance()->getConsole()->addLog(e.what(), Console::LOGLEVEL_ERROR);
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
				static ImVec2 window_size = ImVec2(0,0);
				if (ImGui::GetWindowSize().x != window_size.x || ImGui::GetWindowSize().y != window_size.y) {
					window_size = ImGui::GetWindowSize();
					s_default_texture.create(window_size.x, std::max(window_size.y - 35, 10.f));
					s_default_texture.clear(sf::Color::White);

					sf::Sprite logo;
					logo.setTexture(Resources::LOGO_PE);
					logo.setScale(.2, .2);
					auto tex_size = logo.getTexture()->getSize();
					logo.setOrigin(tex_size.x / 2, tex_size.y / 2);
					logo.setPosition(window_size.x / 2, window_size.y / 2);

					s_default_texture.draw(logo);
				}
				ImGui::Image(s_default_texture);
				ImGui::End();
			}
		}
	}

};