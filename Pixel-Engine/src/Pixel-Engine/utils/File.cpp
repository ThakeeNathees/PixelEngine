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

	int File::mkDir(const std::string& path, bool make_sub_dir)
	{
		if (File::isDirectory(path)) {
			PE_WARN("can't make file, file already exist : ./{0}", path);
			return FILE_ALREADY_EXISTS;
		}
		int error=-1;
		if (!make_sub_dir) {
			error = _mkdir(path.c_str());
			if (!error) PE_SUCCESS("folder created: {0}", path);
		} else {
			std::vector<std::string> vect_split;
			str_split(vect_split, path, "/");
			std::string sub_path = "";
			for (auto sub_file : vect_split) {
				error = _mkdir( ( (sub_path+=(sub_file+"/")) ).c_str() );
				if (!error) PE_SUCCESS("folder created: {0}", sub_path);
			}
		}
		if (!error) return FILE_SUCCESS;
		PE_WARN("can't make file, try : mkDir(\"./{0}\", true)",path);
		return FILE_FAILED;

	}

	int File::rmDir(const std::string& path, bool del_sub_dir)
	{
		int error;
		if (!del_sub_dir) {
			error = _rmdir(path.c_str());
			if (!error) PE_RED("folder deleted: {0}",path);
			if (error && File::isDirectory(path)) {
				PE_WARN("can't delete file with sub folder, use : File::rmDir(\"./{0}\", true)",path);
				return FILE_NOT_EMPTY;
			}
			/// recursive delete
		} else {
			File file; file.open(path);
			for (auto f : file.getFiles()) {
				if (!File::isDirectory(f)) {
					error = remove(f.c_str());
					if (!error) PE_RED("file   deleted: {0}",f);
				}
				else {
					error = File::rmDir(f, true);
				}
			}
			error = _rmdir(path.c_str());
			if (!error) PE_RED("folder deleted: {0}",path);
		}
		if (!error) return FILE_SUCCESS;
		PE_RED("deletion was failed! ./{0}", path);
		return FILE_FAILED;
	}

	void File::test(std::string path)
	{
		std::vector<std::string>v;
		File f; f.open(path);
		for (auto name : f.getFiles()) {
			str_split(v, name, "/"); std::string tab = "";
			for (int i = 0; i < v.size() - 2; i++) tab += "\t";tab += "+----";
			if (!File::isDirectory(name)) {
				std::cout <<  tab + v[v.size()-1] << std::endl;
			}
			else
			{
				std::cout <<  tab + v[v.size()-1]+ "/" << std::endl;
				test(name);
			}
		}
	}
	
	void File::getFileTree( std::stringstream& ss, std::string path)
	{
		std::vector<std::string>v;
		File f; f.open(path);
		for (auto name : f.getFiles()) {

			str_split(v, name, "/"); std::string tab = "";
			for (int i = 0; i < v.size() - 2; i++)  // if v = [ ".", "folder1", "folder2", "file.txt" ]
				tab += "\t";						// need 2 tabs and 1 +----
			tab += "+----";
			ss << tab << v[v.size() - 1];
			
			if (!File::isDirectory(name)) {
				ss << std::endl;
			}
			else
			{
				ss << "/" << std::endl;
				getFileTree(ss, name);
			}
		}
	}

	/////////////////// static

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
		for (auto file_name : m_files) {
			ss << file_name << std::endl; ;
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