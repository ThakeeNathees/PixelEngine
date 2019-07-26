#pragma once

#include "..//Core.h"

#include <dirent.h>    // loop throught files
#include <sys/stat.h>  // check if a file diractory
#include <direct.h>    // create folder


namespace pe
{
	class PIXEL_ENGINE_API File
	{
		enum { FILE_SUCCESS = 0, FILE_FAILED = -1, FILE_ALREADY_EXISTS = 1, };
	public:
		inline File() : m_path("./"), dir(NULL), ent(NULL) {}
		inline ~File(){
			delete dir;
		}
		
		static bool isDirectory(const std::string& path);
		static int mkDir(const std::string& path);


		int open(const std::string& path = "./");
		std::vector<std::string> getFiles() const;
		std::string toString() const;

	private:
		void updateFiles();
		std::string m_path;
		DIR* dir;
		struct dirent* ent;
		std::vector<std::string> m_files; // if filename ends with '/' it's a directory

	};
}