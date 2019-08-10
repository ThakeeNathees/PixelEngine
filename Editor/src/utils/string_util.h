#pragma once

namespace utils
{
	struct FileFormats
	{
		static const char* TEXT[];
		static const char* IMAGE[];
		static const char* BINARY[];
		//static const char* SCENE[0];
		//static const char* ANIM[0];

	};
	

	bool isEndsWith( const std::string& fullString, const std::string& ending );
	bool isPathImage( const std::string& file_path );


}