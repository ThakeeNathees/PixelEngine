#include "pch.h"
#include "entities.h"

#include <pybind11/embed.h>
namespace py = pybind11;

#include "api/Application.h"
#include "..//PythonObject.h"


void register_object(py::module m)
{

	py::class_<pe::Object, sf::Transformable, pe::Drawable, pe::Asset> pe_object(m, "Object", py::dynamic_attr());

	py::enum_<pe::Object::ObjectType>(pe_object, "ObjectType")
		.value("CPP_OBJECT", pe::Object::ObjectType::CPP_OBJECT)
		.value("PYTHON_OBJECT", pe::Object::ObjectType::PYTHON_OBJECT)
		;

	pe_object
		//.def(py::init<>())
		
		/* runtime objects nomore
		.def_static("new", [](const std::string& class_name, pe::Object::ObjectType type) -> pe::Object*
			{
				if (class_name == std::string("") && type == pe::Object::ObjectType::CPP_OBJECT) {
					return pe::Assets::newAsset<pe::Object>();
				}
				pe::Object* obj = nullptr;
				switch (type) {
				case pe::Object::ObjectType::CPP_OBJECT:
					return pe::Assets::newObject(class_name);
					break;
				case pe::Object::ObjectType::PYTHON_OBJECT:{
					obj = new PythonObject(class_name);
					pe::Assets::addAsset(obj);
					return obj;
				}
				default:
					return obj;
				}
			}, py::arg("class_name")="", py::arg("type")=pe::Object::ObjectType::CPP_OBJECT, 
			py::return_value_policy::reference)
		*/

		/* will defined in client_src.py
		inline virtual void sceneEntered(Scene*) {};			def sceneEntered(self, scene): ...
		inline virtual void process(double dt) {};				def process(self, dt): ...
		inline virtual void input(Event& event) {}				def input(self, event): ...
		inline virtual void recieveSignal(Signal& signal) {}	def recieveSignal(self, signal): ...
		virtual void drawCall() const;							def drawCall(self) : ...
		*/

		// draw methods
		.def("draw", [](pe::Object& self, const sf::Drawable& drawable) { self.draw(drawable); })
		.def("drawText", [](pe::Object& self, const std::string& str, const sf::Vector2f& position, const sf::Color& color, float scale) {
				pe::Text text; text.setString(str); text.setPosition(position); text.setFillColor(color); text.setScale(scale, scale);
				self.draw(text);
			}, py::arg("string"), py::arg("position")=sf::Vector2f(0,0), py::arg("color")=sf::Color::White, py::arg("scale")=1)
		.def("drawSelf", [](pe::Object& self) {self.drawSelf(); })

		.def("drawRectangle", (void(pe::Object::*)(float, float, float, float, const sf::Color&, bool, float)const) & pe::Object::drawRectangle,
			py::arg("x"), py::arg("y"), py::arg("width"), py::arg("height"), py::arg("color") = pe::Application::s_default_color, py::arg("outline") = false, py::arg("outline_thickness") = 2
		)
		.def("drawRectangle", (void(pe::Object::*)(const sf::Vector2f&, const sf::Vector2f&, const sf::Color&, bool, float)const) & pe::Object::drawRectangle,
			py::arg("position"), py::arg("size"), py::arg("color") = pe::Application::s_default_color, py::arg("outline") = false, py::arg("outline_thickness") = 2
		)
		.def("drawRectangle", (void(pe::Object::*)(const sf::FloatRect&, const sf::Color&, bool, float)const) & pe::Object::drawRectangle,
			py::arg("rect"), py::arg("color") = pe::Application::s_default_color, py::arg("outline") = false, py::arg("outline_thickness") = 2
		)
		.def("drawRectangle", (void(pe::Object::*)(const sf::RectangleShape&)const) & pe::Object::drawRectangle)


		.def("drawLine", (void(pe::Object::*)(float, float, float, float, float, const sf::Color&)const) & pe::Object::drawLine,
			py::arg("x1"), py::arg("x2"), py::arg("y1"), py::arg("y2"), py::arg("thickness") = 5, py::arg("color") = pe::Application::s_default_color
		)
		.def("drawLine", (void(pe::Object::*)(const sf::Vector2f&, const sf::Vector2f&, float, const sf::Color&)const) & pe::Object::drawLine,
			py::arg("point1"), py::arg("point2"), py::arg("thickness") = 5, py::arg("color") = pe::Application::s_default_color
		)

		.def("drawCircle", (void(pe::Object::*)(float, float, float, const sf::Color&, bool, float)const) & pe::Object::drawCircle,
			py::arg("x"), py::arg("y"), py::arg("r"), py::arg("color") = pe::Application::s_default_color, py::arg("outline") = false, py::arg("thickness") = 2
		)
		.def("drawCircle", (void(pe::Object::*)(const sf::Vector2f&, float, const sf::Color&, bool, float)const) & pe::Object::drawCircle,
			py::arg("position"), py::arg("r"), py::arg("color") = pe::Application::s_default_color, py::arg("outline") = false, py::arg("thickness") = 2
		)

		// draw method end /////////////////////////////////////////////////////////

		.def("emitSignal", &pe::Object::emitSignal)
		.def("getObjectType", &pe::Object::getOjbectType)

		.def("setPosition", (void(pe::Object::*)(float, float)) &pe::Object::setPosition)
		.def("setPosition", (void(pe::Object::*)(const sf::Vector2f&)) &pe::Object::setPosition)
		.def("setRotation", &pe::Object::setRotation)
		.def("setScale", (void(pe::Object::*)(float, float)) &pe::Object::setScale)
		.def("setScale", (void(pe::Object::*)(const sf::Vector2f&)) &pe::Object::setScale)
		.def("setOrigin", (void (pe::Object::*)(float, float)) &pe::Object::setOrigin)
		.def("setOrigin", (void (pe::Object::*)(const sf::Vector2f&)) &pe::Object::setOrigin)

		.def("move", (void(pe::Object::*)(float, float) ) &pe::Object::move)
		.def("move", (void(pe::Object::*)(const sf::Vector2f&) ) &pe::Object::move)
		.def("rotate",  &pe::Object::rotate)
		.def("scale", (void(pe::Object::*)(float, float))&pe::Object::scale)
		.def("scale", (void(pe::Object::*)(const sf::Vector2f&))&pe::Object::scale)

		.def("setSprite", &pe::Object::setSprite)
		.def("setZindex", &pe::Object::setZindex)
		.def("setArea", &pe::Object::setArea, py::arg("area")=nullptr)
		.def("addAnimation", &pe::Object::addAnimation)
		.def("addTimer", &pe::Object::addTimer)

		.def("setPersistence", &pe::Object::setPersistence)
		.def("isPersistence", &pe::Object::isPersistence)
		.def("clear", &pe::Object::clear)
		

		.def("getApplication", [](pe::Object& self)-> pe::Application* { if (self.hasApplication()) return &self.getApplication(); return nullptr;  }, py::return_value_policy::reference)
		.def("getScene", [](pe::Object& self)->pe::Scene * {if (self.hasScene()) return &self.getScene(); return nullptr;  }, py::return_value_policy::reference)
		.def("getArea", [](pe::Object& self)->pe::Area * { if (self.hasArea()) return &self.getArea(); return nullptr; }, py::return_value_policy::reference)
		.def("getSprite", [](pe::Object& self)->pe::Sprite * { if (self.hasSprite()) return &self.getSprite(); return nullptr; }, py::return_value_policy::reference)
		.def("getTimer", [](pe::Object& self, const std::string& name)->pe::Timer* { if (self.hasTimer(name)) return &self.getTimer(name); return nullptr; }, py::return_value_policy::reference)
		.def("getAnimation", [](pe::Object& self, const std::string& name)->pe::Animation * { if (self.hasAnimation(name)) return &self.getAnimation(name); return nullptr; }, py::return_value_policy::reference)
		.def("getTimers", &pe::Object::getTimers, py::return_value_policy::reference)
		.def("getAnimations", &pe::Object::getAnimations, py::return_value_policy::reference)

		;

	py::class_<PythonObject, pe::Object>(m, "__pyObject");
}

