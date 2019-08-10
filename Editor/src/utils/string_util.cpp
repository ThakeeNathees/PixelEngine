
#include "pch.h"
#include "string_util.h"

namespace utils
{
	const char* FileFormats::TEXT[6]   = { ".c",".cpp",".h", ".hpp", ".txt", ".ini" };
	const char* FileFormats::IMAGE[3]  = { ".jpg",".png",".jpeg" };
	const char* FileFormats::BINARY[1] = { ".cjar" };


	// functions
	bool isEndsWith(const std::string& fullString, const std::string& ending) {
		if (fullString.length() >= ending.length()) {
			return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
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