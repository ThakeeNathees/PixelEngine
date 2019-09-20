#pragma once

#include <pybind11/stl.h>
#include "pybind11/embed.h"
namespace py = pybind11;

class FileTree
{
public:
	FileTree(const std::string& root_path = ".") 
		:m_root_path(root_path)
	{
		m_py_filetree = py::module::import("file_tree").attr("FileTree")(m_root_path);
	}

	int getFileCount() {
		return m_py_filetree.attr("files").attr("__len__")().cast<int>();
	}
	int getDirCount() {
		return m_py_filetree.attr("dirs").attr("__len__")().cast<int>();
	}

	std::string getFile(int ind) {
		assert( ind < getFileCount() );
		return m_py_filetree.attr("files").attr("__getitem__")(ind).cast<std::string>();
	}
	py::object getDir(int ind) {
		return  m_py_filetree.attr("dirs").attr("__getitem__")(ind);
	}

	

private:
	std::string m_root_path;
	py::object m_py_filetree;
};
