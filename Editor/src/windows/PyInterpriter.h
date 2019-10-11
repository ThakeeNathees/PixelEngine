#pragma once

#include "core/PyUtils.h"


class PyInterpriter
{
private:
	static PyInterpriter* s_instance;
	PyInterpriter() {
		m_logs.push_back(std::make_pair("Python 3.7.4 interpriter (only single line commands are supports)", 0));
		m_logs.push_back(std::make_pair("Warning : Don't use print, help, other io related functions", 1));
	}
	bool m_set_focus = false; // set focus on input text field
	float m_font_scale = 150;
	char m_input[1024] = {};
	char m_input_temp[1024] = {};
	bool m_scroll_to_bottom = false;
	bool m_enter_released = false;
	sf::Clock m_clock;
	std::vector<std::pair<std::string, int>> m_logs; // int 0 - white ,  1 - yello, 2 - red

	std::vector<std::string> m_inputs; // for up arrow key fill text area
	std::size_t m_inputs_ind = 0; // index in m_inputs

public:
	bool m_open = true; // for main menu bar check box -> public
	static PyInterpriter* getInstance() {
		if (s_instance == nullptr) s_instance = new PyInterpriter();
		return s_instance;
	}
	
	void render() {
		if (m_open) {
			ImGui::Begin("Python Interpriter", &m_open);

			// font scale drag input
			ImGui::SetNextItemWidth(100);
			if (ImGui::DragFloat("font scale", &m_font_scale, 1, 100, 300, "%.3f%%")) {
				if (m_font_scale <= 100) m_font_scale = 100; // TODO: magic number
			} ImGui::SameLine();
			if (ImGui::ImageButton(Resources::getOtherIcon("clear_log"))) {
				m_logs.clear();
				m_inputs.clear();
				m_inputs_ind = 0;
				m_logs.push_back(std::make_pair("Python 3.7.4 interpriter (only single line commands are supports)", 0));
				m_logs.push_back(std::make_pair("Warning : Don't use print, help, other io related functions", 1));
			}

			ImGui::BeginChild("__repr__", ImVec2(0, -30), true);

			// change font scale
			static float last_font_scale = 100;
			if (last_font_scale != m_font_scale) {
				last_font_scale = m_font_scale;
				ImGui::SetWindowFontScale(m_font_scale / 100);
			}

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
			if (m_set_focus) {
				m_set_focus = false;
				ImGui::SetKeyboardFocusHere();
			}
			if (ImGui::InputText("input", m_input, sizeof(m_input))) {}

			// keyboard short cut
			/*
			if (  ImGui::IsRootWindowFocused() && (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && m_clock.restart().asSeconds() > .1) {
				ImGui::SetKeyboardFocusHere();
				m_set_focus = true;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_inputs_ind != 0) m_inputs_ind--;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) m_inputs_ind++;
				else if (m_inputs_ind >= m_inputs.size()) m_inputs_ind = m_inputs.size() - 1;
				if (m_inputs.size() > 0 && m_inputs_ind < m_inputs.size() && m_inputs_ind >=0) {
					int i = 0;
					while (m_inputs[m_inputs_ind].c_str()[i]) m_input[i] = m_inputs[m_inputs_ind].c_str()[i++];
					m_input[i] = '\0';
				}
			}
			*/


			// TODO: ignore input(), help, ... 
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && ImGui::IsWindowFocused()) {
				m_set_focus = true;
				m_scroll_to_bottom = true;
				m_inputs_ind = m_inputs.size();
				if (m_input[0] != '\0' && m_clock.restart().asSeconds() > .1) { // clock used for duplicate(double) inputs
					m_inputs.push_back(std::string(m_input));
					try {
						py::exec(std::string(m_input));
						try {
							auto result = py::str(py::eval(std::string(m_input))).cast<std::string>();
							result = std::string(">>> ").append(std::string(m_input)).append("\n").append(result);
							m_logs.push_back(std::make_pair(result, 0));
						}
						catch (const std::exception&) {
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