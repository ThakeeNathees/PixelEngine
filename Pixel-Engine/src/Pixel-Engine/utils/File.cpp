#include "pepch.h"
#include "File.h"

namespace pe
{
	// static
	bool File::isDirectory(const std::string& path)
	{
		struct stat buffer;
		return (stat((path +"/").c_str(), &buffer) == 0);
	}

	int File::mkDir(const std::string& path)
	{
		int error = _mkdir(path.c_str());
		if (File::isDirectory(path)) return FILE_ALREADY_EXISTS;
		if (!error) return FILE_SUCCESS;
		return FILE_FAILED;
	}

	int File::open(const std::string& path)
	{
		(path[path.size() - 1] != '/') ? m_path = path + "/" : m_path = path; // update m_path
		dir = opendir(m_path.c_str());
		if (dir != NULL) {
			updateFiles();
			return FILE_SUCCESS;
		}
		else return FILE_FAILED;
	}

	// getters
	std::vector<std::string> File::getFiles() const
	{
		return m_files;
	}

	std::string File::toString() const
	{
		std::stringstream ss;
		for (auto file : m_files) {
			ss << file << std::endl; ;
		}
		return ss.str();
		
	}



	// private
	void File::updateFiles()
	{
		m_files.clear();
		while (ent = readdir(dir))
		{
			std::string name = ent->d_name;
			if (name != "." && name != "..") {

			if (isDirectory(name))
				m_files.push_back( m_path + name + "/" );
			else m_files.push_back( m_path + name );
			}
			 
			
		}
	}

}