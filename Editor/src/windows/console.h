#pragma once



class Console
{
public:
	enum LogLevel {
		_ERROR=0, _WARNING, _INFO, _SUCCESS,
	};
	struct LogMsg
	{
		LogLevel level=_INFO;
		std::string msg;
	};

	static void renderConsole();
	static void addLog(LogMsg log);

private:
	static bool s_p_open;
	static bool s_scroll_to_bottom;
	static char s_input_buff[256];
	static std::vector<LogMsg> s_logs;
};
