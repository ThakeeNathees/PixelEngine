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

#ifdef _WIN32
#include <direct.h>
#define getCurrentDir _getcwd
#define changeDir _chdir
#else
#include "unistd.h"
#define getCurrentDir getcwd
#define changeDir chdir
#endif


#include <iostream>
#include <fstream>
#include <stdio.h>
#ifdef _WIN32
	#define sprintf sprintf_s
#endif

#include <ctime>
// for ctime_s
	

class Logger
{
public:
	Logger() = delete;
	static void init( const std::string& path ) {
		s_is_init = true;
		s_path = path;
		s_outfile.open(s_path.c_str());
		s_outfile << "";
		s_outfile.close();

#ifdef _WIN32
		time_t result = time(NULL);
		char str[26];
		ctime_s(str, sizeof str, &result);
		sprintf(Logger::s_buf, str);
		Logger::log();
#endif

	}

	static void log() {
		s_outfile.open(s_path.c_str(), std::fstream::app);
		s_outfile << s_buf << "\n";
		s_outfile.close();
	}

	static char s_buf[4096];
	static std::string s_path;
	static std::ofstream s_outfile;
	static bool s_is_init;
};

#define PE_LOG( str, ... ) \
{sprintf( Logger::s_buf, str, __VA_ARGS__); \
Logger::log();}

#define PE_CONSOLE_LOG(x, ...) {printf("[pe] ");printf( x, __VA_ARGS__ ); printf("\n");}
