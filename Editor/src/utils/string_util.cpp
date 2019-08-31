
#include "pch.h"
#include "string_util.h"

namespace utils
{
	const char* FileFormats::TEXT[]   = { ".c",".cpp",".h", ".hpp", ".txt", ".ini" };
	const char* FileFormats::IMAGE[]  = { ".jpg",".png",".jpeg" };
	const char* FileFormats::BINARY[] = { ".exe" };


	// functions
	bool isEndsWith(const std::string& fullString, const std::string& ending) {
		if (fullString.length() >= ending.length()) {
			return (fullString.compare(fullString.length() - ending.length(), ending.length(), ending) == 0);
		}
		else {
			return false;
		}
	}

	bool isPathImage(const std::string& file_path) {
		int count = sizeof(FileFormats::IMAGE) / sizeof(char*);
		for (int i = 0; i < count; i++) {
			if( isEndsWith(file_path, FileFormats::IMAGE[i]) ) return true;
		}
		return false;
	}
	bool isPathText(const std::string& file_path) {
		int count = sizeof(FileFormats::TEXT) / sizeof(char*);
		for (int i = 0; i < count; i++) {
			if (isEndsWith(file_path, FileFormats::TEXT[i])) return true;
		}
		return false;
	}
}