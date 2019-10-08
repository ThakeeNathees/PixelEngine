#pragma once

// for general use cli instance console

class Console
{
public:

	enum LogLevel { // TODO: ADD LOG LEVEL COSTOM AND CREATE CUSTOM COLOR FROM sf::Color -> for python user
		LOGLEVEL_INFO		= 0,
		LOGLEVEL_SUCCESS	= 1,
		LOGLEVEL_WARNING	= 2,
		LOGLEVEL_ERROR		= 3,
	};
	struct Log {
		Log(const std::string& log, LogLevel level = LogLevel::LOGLEVEL_INFO) {
			m_log = log;
			m_level = level;
		}
		std::string m_log;
		LogLevel m_level;

	};

	bool m_open = true; // main menu bar need &m_open 
private:
	bool m_scroll_to_bottom = false;
	std::vector<Log> m_logs;

public:
	// for python to call
	void addLog(const std::string& msg, int level=0) {
		assert( level <=3 );
		Log log(msg, (LogLevel)level);
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
			ImGui::BeginChild("ScrollingRegion", ImVec2(0, 0), true); // Leave room for 1 separator + 1 InputText

			for (auto& log : m_logs) {
				switch (log.m_level) {
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



