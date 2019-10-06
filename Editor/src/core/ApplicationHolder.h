#pragma once

#include "core/cli/CLI.h"

class ApplicationHolder
{
private:
	static bool s_is_running;

	static std::string s_proj_file_name;
	static pe::Application* s_application;
	static sf::RenderTexture s_render_texture;
	ApplicationHolder() = delete;
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
		}
		catch (const std::exception& e){
			CLI::getInstance()->getConsole()->addLog(e.what(), 3);
		}

	}

	static void render() {
		if (s_is_running) {
			ImGui::Begin("Applicaton window", &s_is_running);
			ImGui::SetWindowSize( ImVec2(s_application->getWindowSize().x, s_application->getWindowSize().y), ImGuiCond_Appearing );

			ImGui::Image(ApplicationHolder::getRenderTexture());

			ImGui::End();
		}
	}

};