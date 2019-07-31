#include "pch.h"
#include "console.h"

#define ARR_SIZE(_ARR) (int)(sizeof(_ARR)/sizeof(*_ARR))

// function implimentation
// TODO: change exec function as engine's 
int exec(std::string& result, const char* cmd) { // if success return 0;
	char buffer[128];
	result = "";
	FILE* pipe = _popen(cmd, "r");
	if (!pipe) return 1;
	try {
		while (fgets(buffer, sizeof buffer, pipe) != NULL) {
			result += buffer;
		}
	}
	catch (...) {
		_pclose(pipe);
		return 2;
	}
	_pclose(pipe);
	return 0;
}


// member field
bool Console::s_p_open = true;
bool Console::s_scroll_to_bottom = true;
std::vector<Console::LogMsg> Console::s_logs;
char Console::s_input_buff[256];

void Console::addLog(LogMsg log) {
	s_scroll_to_bottom = true;
	s_logs.push_back(log);
}

	

int text_edit_callback(ImGuiInputTextCallbackData* data) { return 1; } // for text box
void Console::renderConsole()
{
	if (s_p_open) {
		ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);
		ImGui::Begin("Console", &s_p_open, ImGuiWindowFlags_HorizontalScrollbar);

		if (ImGui::Button("add error")) {
			addLog({_ERROR, "dummy error!"});
		}
		
		// scrolling region
		const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing(); // 1 separator, 1 input text
		ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar); // Leave room for 1 separator + 1 InputText

		for (auto log : s_logs) {
			if (log.level == _INFO)
				ImGui::TextUnformatted(log.msg.c_str());
			else if (log.level == _ERROR) {
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.4f, 0.4f, 1.0f));
				ImGui::TextUnformatted(log.msg.c_str());
				ImGui::PopStyleColor();
			}
			else if (log.level == _WARNING) {
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 0.4f, 1.0f));
				ImGui::TextUnformatted(log.msg.c_str());
				ImGui::PopStyleColor();
			}
			else if (log.level == _SUCCESS) {
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.4f, 1.0f, 0.4f, 1.0f));
				ImGui::TextUnformatted(log.msg.c_str());
				ImGui::PopStyleColor();
			}

		}

		if (s_scroll_to_bottom) ImGui::SetScrollHereY(1.0f);
		s_scroll_to_bottom = false;

		ImGui::EndChild();
		ImGui::Separator();
		bool reclaim_focus = false;
		if (ImGui::InputText("Input", s_input_buff, ARR_SIZE(s_input_buff), ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory, &text_edit_callback))
		{
			std::string result = "";
			int error = exec(result, s_input_buff);
			if (!error) addLog({ _INFO, result });
			else addLog({ _ERROR, "[error] some error occured executing the command" });
			strcpy_s(s_input_buff, "");
			reclaim_focus = true;
		}
		if (reclaim_focus) ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget

		ImGui::End();
	}
}
