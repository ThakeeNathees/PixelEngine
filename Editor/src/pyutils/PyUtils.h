#pragma once

class PyUtils
{
private:
	PyUtils() {
		m_math_util = py::module::import("math_util");
		m_str_util = py::module::import("str_util");
		m_file_util = py::module::import("file_util");
		m_py_os = py::module::import("os");
	}
	static PyUtils* s_instance;
	py::module m_math_util;
	py::module m_str_util;
	py::module m_file_util;
	py::module m_py_os;


public:
	static PyUtils* getInstance() {
		if (s_instance == nullptr) s_instance = new PyUtils();
		return s_instance;
	}

	py::module& getMathUtil() {
		return m_math_util;
	}
	py::module& getStrUtil() {
		return m_str_util;
	}
	py::module& getFileUtil() {
		return m_file_util;
	}

	py::module& getOs() {
		return m_py_os;
	}
};