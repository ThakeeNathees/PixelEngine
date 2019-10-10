#pragma once

#include "PyUtils.h"

class Resources
{
public:


	// textures
	static sf::Texture LOGO;
	static sf::Texture LOGO_PE;
	static sf::Texture PNG_BG;

	static sf::Texture& getFileFormatIcon(const std::string& name) {
		assert( s_file_format_icons.find(name) != s_file_format_icons.end() && name.c_str() );
		return s_file_format_icons[name];
	}
	static sf::Texture& getMenuIcon(const std::string& name) {
		assert(s_menu_icons.find(name) != s_menu_icons.end() && name.c_str() );
		return s_menu_icons[name];
	}
	static sf::Texture& getOtherIcon(const std::string& name) {
		assert(s_other_icons.find(name) != s_other_icons.end() && name.c_str() );
		return s_other_icons[name];
	}
	static ImFont* getFont(const std::string& name) {
		assert(s_fonts.find(name) != s_fonts.end() && name.c_str());
		return s_fonts[name];
	}


	static void addFileFormatIcon(const std::string& name, const sf::Texture& tex) {
		s_file_format_icons[name] = tex;
	}
	static void addMenuIcon(const std::string& name, const sf::Texture& tex) {
		s_menu_icons[name] = tex;
	}
	static void addOtherIcon(const std::string& name, const sf::Texture& tex) {
		s_other_icons[name] = tex;
	}
	static void addFont(const std::string& name, ImFont* font) {
		s_fonts[name] = font;
	}
	
	static std::map<std::string, ImFont*>& getFonts() {
		return s_fonts;
	}

private:
	Resources() {}
	static std::map<std::string, sf::Texture> s_file_format_icons;
	static std::map<std::string, sf::Texture> s_menu_icons;
	static std::map<std::string, sf::Texture> s_other_icons;
	static std::map<std::string, ImFont*> s_fonts;

public:

	static void drawFileIcon(const std::string& file_name) {
		std::string format = PyUtils::getInstance()->getFileUtil().attr("getFileFormat")(file_name).cast<std::string>();
		if (format == std::string("py")) { ImGui::Image(Resources::getFileFormatIcon("file_py"));  return; }
		if (format == std::string("peproj")) { ImGui::Image(Resources::getFileFormatIcon("file_peproj")); return; }
		if (format == std::string("txt")) { ImGui::Image(Resources::getFileFormatIcon("file_text"));  return; }
		if (format == std::string("ini")) { ImGui::Image(Resources::getFileFormatIcon("file_text"));  return; }
		if (format == std::string("xml")) { ImGui::Image(Resources::getFileFormatIcon("file_xml")); return; }
		if (format == std::string("pyc")) { ImGui::Image(Resources::getFileFormatIcon("file_pyc")); return; }
		if (format == std::string("cpp")) { ImGui::Image(Resources::getFileFormatIcon("file_cpp")); return; }
		if (format == std::string("h")) { ImGui::Image(Resources::getFileFormatIcon("file_h"));  return; }
		if (format == std::string("hpp")) { ImGui::Image(Resources::getFileFormatIcon("file_hpp"));  return; }
		if (format == std::string("ttf")) { ImGui::Image(Resources::getFileFormatIcon("file_ttf"));  return; }
		// image files
		if (format == std::string("png")) { ImGui::Image(Resources::getFileFormatIcon("file_png"));return; }
		if (format == std::string("jpg")) { ImGui::Image(Resources::getFileFormatIcon("file_png"));return; }
		if (format == std::string("jpeg")) { ImGui::Image(Resources::getFileFormatIcon("file_png")); return; }
		// binary files
		if (format == std::string("exe")) { ImGui::Image(Resources::getFileFormatIcon("file_bin"));  return; }
		if (format == std::string("lib")) { ImGui::Image(Resources::getFileFormatIcon("file_bin"));  return; }
		if (format == std::string("dll")) { ImGui::Image(Resources::getFileFormatIcon("file_dll"));  return; }
		if (format == std::string("obj")) { ImGui::Image(Resources::getFileFormatIcon("file_obj"));  return; }

		ImGui::Image(Resources::getFileFormatIcon("file_unknown"));
	}
	
};