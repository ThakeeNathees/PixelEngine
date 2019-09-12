#pragma once

#include <pybind11/pybind11.h>
namespace py = pybind11;

#include "api/Application.h"

class PythonObject : public pe::Object
{
public:
	inline PythonObject( const std::string& module_name) {
		this;
		m_object_type = pe::Object::ObjectType::PYTHON_OBJECT;
		m_module = py::module::import(module_name.c_str());
		m_class_name = module_name;
		init();
	}

	inline void init() {
		if (py::hasattr(m_module, "init")) m_module.attr("init")(py::cast(this));
	}
	inline void sceneEntered(pe::Scene* scene) override {
		if (py::hasattr(m_module, "sceneEntered")) m_module.attr("sceneEntered")(py::cast(this),scene);
	}
	inline void process(double dt) {
		if (py::hasattr(m_module, "process")) m_module.attr("process")(py::cast(this), dt);
	}
	inline void handleEvent(pe::Event& event) override {
		if (py::hasattr(m_module, "handleEvent")) m_module.attr("handleEvent")(py::cast(this), event);
	}
	inline void recieveSignal(pe::Signal& signal) override {
		if (py::hasattr(m_module, "recieveSignal")) m_module.attr("recieveSignal")(py::cast(this), signal);
	}
	inline void drawCall() const override {
		if (py::hasattr(m_module, "drawCall")) m_module.attr("drawCall")(py::cast(this));
		else pe::Object::drawCall();
	}

	inline void scriptReload() override {
		m_module.reload();
	}

private:
	py::module m_module;
};
