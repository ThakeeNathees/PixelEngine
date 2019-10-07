#pragma once

#include "pyutils/PyUtils.h"


class PyInterpriter
{
private:
	static PyInterpriter* s_instance;
	PyInterpriter() {
		m_logs.push_back(std::make_pair("Python 3.7.4 interpriter (only single line commands are supports)", 0));
		m_logs.push_back(std::make_pair("Warning : Don't use print, help, other io related functions", 1));
	}
	bool m_open = true;
	char m_input[1024] = {};
	bool m_scroll_to_bottom = false;
	bool m_enter_released = false;
	sf::Clock m_clock;
	std::vector<std::pair<std::string, int>> m_logs; // int 0 - white ,  1 - yello, 2 - red

public:
	static PyInterpriter* getInstance() {
		if (s_instance == nullptr) s_instance = new PyInterpriter();
		return s_instance;
	}
	
	void render() {
		if (m_open) {
			ImGui::Begin("Python Interpriter", &m_open);
			ImGui::BeginChild("__repr__", ImVec2(0, -30), true);
			for (auto pair : m_logs) {
				switch (pair.second) {
				case 0: 
					ImGui::TextWrapped(pair.first.c_str()); break;
				case 1:
					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 0.4f, 1.0f));
					ImGui::TextWrapped(pair.first.c_str());
					ImGui::PopStyleColor(); break;
				case 2:
					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.4f, 0.4f, 1.0f));
					ImGui::TextWrapped(pair.first.c_str());
					ImGui::PopStyleColor(); break;
				}
			}
			if (m_scroll_to_bottom) { ImGui::SetScrollHereY(1.0f); m_scroll_to_bottom = false; }
			ImGui::EndChild();
			ImGui::Text(">>>"); ImGui::SameLine();
			if (ImGui::InputText("input", m_input, sizeof(m_input))) {}

			// TODO: ignore input(), help, ... 
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && ImGui::IsWindowFocused()) {
				ImGui::SetKeyboardFocusHere(0);
				m_scroll_to_bottom = true;
				if (m_input[0] != '\0' && m_clock.restart().asSeconds() > .1) { // clock used for duplicate(double) inputs
					try {
						py::exec(std::string(m_input));
						try {
							auto result = py::str(py::eval(std::string(m_input))).cast<std::string>();
							result = std::string(">>> ").append(std::string(m_input)).append("\n").append(result);
							m_logs.push_back(std::make_pair(result, 0));
						}
						catch (const std::exception & e) {
							auto result = std::string(">>> ").append(std::string(m_input));
							m_logs.push_back(std::make_pair(result, 0));
						}
					}
					catch (const std::exception & e) {
						auto inp = std::string(">>> ").append(std::string(m_input));
						m_logs.push_back(std::make_pair(inp, 0));
						m_logs.push_back(std::make_pair(e.what(), 2));
					}
				}
				else if (m_enter_released){
					m_logs.push_back(std::make_pair(">>> ", 0));
				}
				m_input[0] = '\0';

			} // input end

			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) m_enter_released = true;
			else m_enter_released = false;

			ImGui::End();
			
		}
	}

};