#pragma once

// for general use cli instance console
#include "core/Resources.h"

class Console
{
public:
	enum LogLevel { // TODO: ADD LOG LEVEL COSTOM AND CREATE CUSTOM COLOR FROM sf::Color -> for python user
		LOGLEVEL_CUSTOM		= -1,
		LOGLEVEL_INFO		= 0,
		LOGLEVEL_SUCCESS	= 1,
		LOGLEVEL_WARNING	= 2,
		LOGLEVEL_ERROR		= 3,
	};
	struct Log {
		Log(const std::string& log, LogLevel level = LogLevel::LOGLEVEL_INFO, sf::Color custom_color = sf::Color::White) {
			m_log = log;
			m_level = level;
			m_custom_log_color = custom_color;
		}
		std::string m_log;
		LogLevel m_level;
		sf::Color m_custom_log_color;
	};

	Console() {
		addLog("**********  Pixel-Engine Console [Version 1.0]  **********", -1, sf::Color(64,196,255));
	}

	bool m_open = true; // main menu bar need &m_open 
private:
	bool m_scroll_to_bottom = false;
	float m_font_scale = 100;
	std::vector<Log> m_logs;

public:
	// for python to call
	void addLog(const std::string& msg, int level=0, sf::Color custom_color = sf::Color::White) {
		assert( level <=3 && level >=-1 );
		Log log(msg, (LogLevel)level, custom_color);
		addLog(log);
	}

	void addLog(Log log) {
		m_logs.push_back(log);
		m_scroll_to_bottom = true;

		// maintain size
		static int MAX_LOG_SIZE = 50;
		if (m_logs.size() > MAX_LOG_SIZE) {
			while(m_logs.size() > MAX_LOG_SIZE) m_logs.erase(m_logs.begin());
		}
	}

	void render() {
		//ImGui::SetNextWindowSize(ImVec2(700, 300), ImGuiCond_Once);
		if (m_open) {
			ImGui::Begin("ConsoleWindow", &m_open);

			// font scale drag input
			ImGui::SetNextItemWidth(100);
			if (ImGui::DragFloat("font scale", &m_font_scale, 1, 100, 300, "%.3f%%")) {
				if (m_font_scale <= 100) m_font_scale = 100; // TODO: magic number
			} ImGui::SameLine();
			if (ImGui::ImageButton(Resources::getOtherIcon("clear_log"))) {
				m_logs.clear();
				addLog("**********  Pixel-Engine Console [Version 1.0]  **********", -1, sf::Color(64, 196, 255));
			}

			ImGui::BeginChild("ScrollingRegion", ImVec2(0, 0), true); 

			// change font scale
			static float last_font_scale = 100;
			if (last_font_scale != m_font_scale) {
				last_font_scale = m_font_scale;
				ImGui::SetWindowFontScale(m_font_scale/100);
			}
			for (auto& log : m_logs) {
				switch (log.m_level) {
				case LogLevel::LOGLEVEL_CUSTOM:
					ImGui::PushStyleColor(ImGuiCol_Text, log.m_custom_log_color);
					ImGui::TextWrapped(log.m_log.c_str());
					ImGui::PopStyleColor(); break;
				case LogLevel::LOGLEVEL_INFO:
					ImGui::TextWrapped(log.m_log.c_str()); break;
				case LogLevel::LOGLEVEL_SUCCESS:
					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.4f, 1.0f, 0.4f, 1.0f));
					ImGui::TextWrapped(log.m_log.c_str());
					ImGui::PopStyleColor(); break;
				case LogLevel::LOGLEVEL_WARNING:
					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 0.4f, 1.0f));
					ImGui::TextWrapped(log.m_log.c_str());
					ImGui::PopStyleColor(); break;
				case LogLevel::LOGLEVEL_ERROR:
					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.4f, 0.4f, 1.0f));
					ImGui::TextWrapped(log.m_log.c_str());
					ImGui::PopStyleColor(); break;
				}

			}

			if (m_scroll_to_bottom) ImGui::SetScrollHereY(1.0f);
			m_scroll_to_bottom = false;

			ImGui::EndChild();
			ImGui::End();

		}
	}
};



