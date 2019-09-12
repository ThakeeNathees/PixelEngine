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
		m_self = py::cast(this);
		init();
	}

	inline void init() {
		if (py::hasattr(m_module, "init")) m_module.attr("init")(m_self);
	}
	inline void sceneEntered(pe::Scene* scene) override {
		if (py::hasattr(m_module, "sceneEntered")) m_module.attr("sceneEntered")(m_self,scene);
	}
	inline void process(double dt) {
		if (py::hasattr(m_module, "process")) m_module.attr("process")(m_self, dt);
	}
	inline void handleEvent(pe::Event& event) override {
		if (py::hasattr(m_module, "handleEvent")) m_module.attr("handleEvent")(m_self, event);
	}
	inline void recieveSignal(pe::Signal& signal) override {
		if (py::hasattr(m_module, "recieveSignal")) m_module.attr("recieveSignal")(m_self, signal);
	}
	inline void drawCall() const override {
		if (py::hasattr(m_module, "drawCall")) m_module.attr("drawCall")(m_self);
		else pe::Object::drawCall();
	}

	inline void scriptReload() override {
		m_module.reload();
	}

private:
	py::object m_self;
	py::module m_module;
};
