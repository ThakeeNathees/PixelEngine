#pragma once

#include "..//Core.h"
#include "util_func.h"

#include <dirent.h>    // loop throught files (vender folder)
#include <sys/stat.h>  // check if a file diractory
#include <direct.h>    // create folder


namespace pe
{
	class PIXEL_ENGINE_API File
	{
		enum { FILE_SUCCESS = 0, FILE_FAILED = -1, FILE_ALREADY_EXISTS = 1, FILE_NOT_EMPTY=2 };
	public:
		inline File() : m_path("./"), dir(NULL), ent(NULL) {}
		inline ~File(){delete dir;}
		
		static bool isDirectory(const std::string& path);
		static int mkDir(const std::string& path, bool make_sub_dir = false);
		static int rmDir(const std::string& path, bool del_sub_dir = false);
		static void getFileTree(std::stringstream& out, std::string path = "."); // for debugging

		static void test(std::string path = ".");

		int open(const std::string& path = "./");
		std::vector<std::string> getFiles() const;
		std::string toString() const;

	private:
		void updateFiles();
		std::string m_path;
		DIR* dir;
		struct dirent* ent;
		std::vector<std::string> m_files;

	};
}