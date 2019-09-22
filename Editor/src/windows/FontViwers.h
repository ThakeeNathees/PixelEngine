#pragma once

#include "pch.h"
class FontViwers
{

public:
	struct FontData
	{
		FontData(const std::string& _path){
			path = _path;
			bool success = font.loadFromFile(path); // TODO: error handle
			sf::Text text(
				std::string(
					"Lorem ipsum dolor sit amet, consectetur \n"
					"adipiscing elit, sed do eiusmod tempor \n"
					"incididunt ut labore et dolore magna aliqua.\n"
					"Ut enim ad minim veniam, quis nostrud \n"
					"exercitation ullamco laboris nisi ut aliquip\n"
					"ex ea commodo consequat. Duis aute irure dolor\n"
					"in reprehenderit in voluptate velit esse cillum\n"
					"dolore eu fugiat nulla pariatur. Excepteur sint\n"
					"occaecat cupidatat non proident, sunt in \n"
					"culpa qui officia deserunt mollit anim id est laborum.\n"
					"\n"
					"Morbi tristique senectus et netus et malesuada \n"
					"fames ac turpis. Proin sagittis nisl rhoncus mattis\n"
					"rhoncus urna neque viverra. Pulvinar elementum integer\n"
					"enim neque volutpat ac tincidunt vitae. Sagittis nisl\n"
					"rhoncus mattis rhoncus urna neque viverra justo.\n"
					"Aliquam malesuada bibendum arcu vitae elementum\n"
					"curabitur. Condimentum lacinia quis vel eros donec ac.\n"
					"Elementum integer enim neque volutpat ac tincidunt vitae\n"
					"semper quis. A erat nam at lectus urna duis convallis.\n"
					"Adipiscing elit pellentesque habitant morbi tristique\n"
					"senectus et. Mus mauris vitae ultricies leo integer\n"
					"malesuada nunc vel."
				),font
			);
			render_tex.create(text.getCharacterSize()*60, text.getCharacterSize() * 27);
			render_tex.draw(text);
		}
		sf::Font font;
		std::string path;
		bool p_open = true;
		sf::RenderTexture render_tex;
	}; // font data end


	static void openFontViwer(const std::string& path, long long id) {
		if (s_fonts.find(id) == s_fonts.end())
			s_fonts[id] = new FontData(path);
		else s_fonts[id]->p_open = true;
	}

	static void renderFontViwers() {
		for (auto pair : s_fonts) {
			if (pair.second->p_open) {
				ImGui::Begin(pair.second->path.c_str(), &pair.second->p_open, ImGuiWindowFlags_NoScrollbar);
				ImGui::SetWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);
				ImGui::Image(pair.second->render_tex);
				ImGui::End();
			}
		}
	}

private:
	FontViwers() {}
	static std::map<long long, FontData*> s_fonts;


};