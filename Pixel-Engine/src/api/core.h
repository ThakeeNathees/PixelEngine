#pragma once

#ifdef _WIN32

	#define NOMINMAX
	#include <Windows.h>

	#ifdef PE_BUILD_DLL
		#define PIXEL_ENGINE_API __declspec(dllexport)
	#else
		#define PIXEL_ENGINE_API __declspec(dllimport)
	#endif
#else
	#error Pixel-Engine only supports Windows!
#endif 


#include <iostream>
#include <fstream>
#include <stdio.h>
#ifdef _WIN32
	#define sprintf sprintf_s
#endif

class Logger
{
public:
	Logger() = delete;
	static void init( const std::string& path ) {
		s_path = path;
		s_outfile.open(s_path.c_str());
		s_outfile << "";
		s_outfile.close();
	}

	static void log() {
		s_outfile.open(s_path.c_str(), std::fstream::app);
		s_outfile << s_buf << "\n";
		s_outfile.close();
	}

	static char s_buf[4096];
	static std::string s_path;
	static std::ofstream s_outfile;
};

#define PE_LOG( str, ... ) \
sprintf( Logger::s_buf, str, __VA_ARGS__); \
Logger::log()

#define PE_CONSOLE_LOG(x) std::cout << "[pe] " << x << std::endl
