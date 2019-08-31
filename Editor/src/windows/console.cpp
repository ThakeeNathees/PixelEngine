#include "pch.h"
#include "console.h"

#define ARR_SIZE(_ARR) (int)(sizeof(_ARR)/sizeof(*_ARR))

// function implimentation
int execSystemCommand(std::string& result, const char* cmd) { // if success return 0;
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
int execEditorCommand(Console::LogMsg& logmsg, const char* cmd) {
	logmsg.msg = std::string("[error] '").append(std::string(cmd)).append("' is not recognized as an editor command.") ;
	logmsg.level = Console::_ERROR;
	return -1;
	// run some script on editor maybe?
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
			LogMsg logmsg;
			int error = execEditorCommand(logmsg, s_input_buff);
			addLog(logmsg);
			strcpy_s(s_input_buff, ""); // clear the input buffer
			reclaim_focus = true;
		}
		if (reclaim_focus) ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget

		ImGui::End();
	}
}
