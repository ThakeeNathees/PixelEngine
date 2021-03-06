#include "pch.h"
#include "types.h"

#include <pybind11/embed.h>
namespace py = pybind11;

#include "api/misc/Event.h"

void register_event(py::module& m)
{
	py::class_<pe::Event>py_event(m, "Event");
	py::class_<sf::Keyboard>py_keyboard(m, "Keyboard");
	py::class_<sf::Mouse>py_mouse(m,"Mouse");

	py::enum_<sf::Event::EventType>(py_event, "Type")
		.value("CLOSED",					pe::Event::EventType::Closed)
		.value("RESIZED",					pe::Event::EventType::Resized)
		.value("LOST_FOCUS",				pe::Event::EventType::LostFocus)
		.value("GAINED_FOCUS",				pe::Event::EventType::GainedFocus)
		.value("TEXT_ENTERED",				pe::Event::EventType::TextEntered)
		.value("KEY_PRESSED",				pe::Event::EventType::KeyPressed)
		.value("KEY_RELEASED",				pe::Event::EventType::KeyReleased)
		.value("MOUSE_WHEEL_MOVED",			pe::Event::EventType::MouseWheelMoved)
		.value("MOUSE_WHEEL_SCROLLED",		pe::Event::EventType::MouseWheelScrolled)
		.value("MOUSE_BUTTON_PRESSED",		pe::Event::EventType::MouseButtonPressed)
		.value("MOUSE_BUTTON_RELEASED",		pe::Event::EventType::MouseButtonReleased)
		.value("MOUSE_MOVED",				pe::Event::EventType::MouseMoved)
		.value("MOUSE_ENTERED",				pe::Event::EventType::MouseEntered)
		.value("MOUSE_LEFT",					pe::Event::EventType::MouseLeft)
		/*
		.value("JoystickButtonPressed",		pe::Event::EventType::JoystickButtonPressed)
		.value("JoystickButtonReleased",	pe::Event::EventType::JoystickButtonReleased)
		.value("JoystickMoved",				pe::Event::EventType::JoystickMoved)
		.value("JoystickConnected",			pe::Event::EventType::JoystickConnected)
		.value("JoystickDisconnected",		pe::Event::EventType::JoystickDisconnected)
		.value("TouchBegan",				pe::Event::EventType::TouchBegan)
		.value("TouchMoved",				pe::Event::EventType::TouchMoved)
		.value("TouchEnded",				pe::Event::EventType::TouchEnded)
		.value("SensorChanged",				pe::Event::EventType::SensorChanged)
		*/
		;

	py::enum_<sf::Keyboard::Key>(py_keyboard, "Key")
		.value("Unknown", sf::Keyboard::Key::Unknown)
		.value("A", sf::Keyboard::Key::A)
		.value("B", sf::Keyboard::Key::B)
		.value("C", sf::Keyboard::Key::C)
		.value("D", sf::Keyboard::Key::D)
		.value("E", sf::Keyboard::Key::E)
		.value("F", sf::Keyboard::Key::F)
		.value("G", sf::Keyboard::Key::G)
		.value("H", sf::Keyboard::Key::H)
		.value("I", sf::Keyboard::Key::I)
		.value("J", sf::Keyboard::Key::J)
		.value("K", sf::Keyboard::Key::K)
		.value("L", sf::Keyboard::Key::L)
		.value("M", sf::Keyboard::Key::M)
		.value("N", sf::Keyboard::Key::N)
		.value("O", sf::Keyboard::Key::O)
		.value("P", sf::Keyboard::Key::P)
		.value("Q", sf::Keyboard::Key::Q)
		.value("R", sf::Keyboard::Key::R)
		.value("S", sf::Keyboard::Key::S)
		.value("T", sf::Keyboard::Key::T)
		.value("U", sf::Keyboard::Key::U)
		.value("V", sf::Keyboard::Key::V)
		.value("W", sf::Keyboard::Key::W)
		.value("X", sf::Keyboard::Key::X)
		.value("Y", sf::Keyboard::Key::Y)
		.value("Z", sf::Keyboard::Key::Z)
		.value("Num0", sf::Keyboard::Key::Num0)
		.value("Num1", sf::Keyboard::Key::Num1)
		.value("Num2", sf::Keyboard::Key::Num2)
		.value("Num3", sf::Keyboard::Key::Num3)
		.value("Num4", sf::Keyboard::Key::Num4)
		.value("Num5", sf::Keyboard::Key::Num5)
		.value("Num6", sf::Keyboard::Key::Num6)
		.value("Num7", sf::Keyboard::Key::Num7)
		.value("Num8", sf::Keyboard::Key::Num8)
		.value("Num9", sf::Keyboard::Key::Num9)
		.value("Escape", sf::Keyboard::Key::Escape)
		.value("LControl", sf::Keyboard::Key::LControl)
		.value("LShift", sf::Keyboard::Key::LShift)
		.value("LAlt", sf::Keyboard::Key::LAlt)
		.value("LSystem", sf::Keyboard::Key::LSystem)
		.value("RControl", sf::Keyboard::Key::RControl)
		.value("RShift", sf::Keyboard::Key::RShift)
		.value("RAlt", sf::Keyboard::Key::RAlt)
		.value("RSystem", sf::Keyboard::Key::RSystem)
		.value("Menu", sf::Keyboard::Key::Menu)
		.value("LBracket", sf::Keyboard::Key::LBracket)
		.value("RBracket", sf::Keyboard::Key::RBracket)
		.value("Semicolon", sf::Keyboard::Key::Semicolon)
		.value("Comma", sf::Keyboard::Key::Comma)
		.value("Period", sf::Keyboard::Key::Period)
		.value("Quote", sf::Keyboard::Key::Quote)
		.value("Slash", sf::Keyboard::Key::Slash)
		.value("Backslash", sf::Keyboard::Key::Backslash)
		.value("Tilde", sf::Keyboard::Key::Tilde)
		.value("Equal", sf::Keyboard::Key::Equal)
		.value("Hyphen", sf::Keyboard::Key::Hyphen)
		.value("Space", sf::Keyboard::Key::Space)
		.value("Enter", sf::Keyboard::Key::Enter)
		.value("Backspace", sf::Keyboard::Key::Backspace)
		.value("Tab", sf::Keyboard::Key::Tab)
		.value("PageUp", sf::Keyboard::Key::PageUp)
		.value("PageDown", sf::Keyboard::Key::PageDown)
		.value("End", sf::Keyboard::Key::End)
		.value("Home", sf::Keyboard::Key::Home)
		.value("Insert", sf::Keyboard::Key::Insert)
		.value("Delete", sf::Keyboard::Key::Delete)
		.value("Add", sf::Keyboard::Key::Add)
		.value("Subtract", sf::Keyboard::Key::Subtract)
		.value("Multiply", sf::Keyboard::Key::Multiply)
		.value("Divide", sf::Keyboard::Key::Divide)
		.value("Left", sf::Keyboard::Key::Left)
		.value("Right", sf::Keyboard::Key::Right)
		.value("Up", sf::Keyboard::Key::Up)
		.value("Down", sf::Keyboard::Key::Down)
		.value("Numpad0", sf::Keyboard::Key::Numpad0)
		.value("Numpad1", sf::Keyboard::Key::Numpad1)
		.value("Numpad2", sf::Keyboard::Key::Numpad2)
		.value("Numpad3", sf::Keyboard::Key::Numpad3)
		.value("Numpad4", sf::Keyboard::Key::Numpad4)
		.value("Numpad5", sf::Keyboard::Key::Numpad5)
		.value("Numpad6", sf::Keyboard::Key::Numpad6)
		.value("Numpad7", sf::Keyboard::Key::Numpad7)
		.value("Numpad8", sf::Keyboard::Key::Numpad8)
		.value("Numpad9", sf::Keyboard::Key::Numpad9)
		.value("F1", sf::Keyboard::Key::F1)
		.value("F2", sf::Keyboard::Key::F2)
		.value("F3", sf::Keyboard::Key::F3)
		.value("F4", sf::Keyboard::Key::F4)
		.value("F5", sf::Keyboard::Key::F5)
		.value("F6", sf::Keyboard::Key::F6)
		.value("F7", sf::Keyboard::Key::F7)
		.value("F8", sf::Keyboard::Key::F8)
		.value("F9", sf::Keyboard::Key::F9)
		.value("F10", sf::Keyboard::Key::F10)
		.value("F11", sf::Keyboard::Key::F11)
		.value("F12", sf::Keyboard::Key::F12)
		.value("F13", sf::Keyboard::Key::F13)
		.value("F14", sf::Keyboard::Key::F14)
		.value("F15", sf::Keyboard::Key::F15)
		.value("Pause", sf::Keyboard::Key::Pause)
		.export_values()
		;
	py::enum_<sf::Mouse::Button>(py_mouse, "Button")
		.value("Left",	sf::Mouse::Button::Left )
		.value("Right", sf::Mouse::Button::Right )
		.value("Middle", sf::Mouse::Button::Middle )
		.value("XButton1", sf::Mouse::Button::XButton1 )
		.value("XButton2", sf::Mouse::Button::XButton2 )
		.export_values()
		;

	py::enum_<sf::Mouse::Wheel>(py_mouse, "Wheel")
		.value("VerticalWheel", sf::Mouse::Wheel::VerticalWheel)
		.value("HorizontalWheel", sf::Mouse::Wheel::HorizontalWheel)
		.export_values()
		;
	///////////////////////////////////////////////////////////////////////

	py::class_<pe::Event::KeyEvent>(py_event, "_KeyEvent")
		.def_readonly("code", &pe::Event::KeyEvent::code )
		.def_readonly("alt", &pe::Event::KeyEvent::alt)
		.def_readonly("control", &pe::Event::KeyEvent::control)
		.def_readonly("shift", &pe::Event::KeyEvent::shift)
		.def_readonly("system", &pe::Event::KeyEvent::system)
		;

	py::class_<pe::Event::MouseMoveEvent>(py_event, "_MouseMoveEvent")
		.def_readonly("x", &pe::Event::MouseMoveEvent::x)
		.def_readonly("y", &pe::Event::MouseMoveEvent::y)
		;

	py::class_<pe::Event::MouseButtonEvent>(py_event, "_MouseButtonEvent")
		.def_readonly("button", &pe::Event::MouseButtonEvent::button)
		.def_readonly("x", &pe::Event::MouseButtonEvent::x)
		.def_readonly("y", &pe::Event::MouseButtonEvent::y)
		;


	py::class_<pe::Event::MouseWheelEvent>(py_event, "_MouseWheelEvent")
		.def_readonly("delta", &pe::Event::MouseWheelEvent::delta)
		.def_readonly("x", &pe::Event::MouseWheelEvent::x)
		.def_readonly("y", &pe::Event::MouseWheelEvent::y)
		;

	py::class_<pe::Event::MouseWheelScrollEvent>(py_event, "_MouseWheelScrollEvent")
		.def_readonly("wheel", &pe::Event::MouseWheelScrollEvent::wheel)
		.def_readonly("delta", &pe::Event::MouseWheelScrollEvent::delta)
		.def_readonly("x", &pe::Event::MouseWheelScrollEvent::x)
		.def_readonly("y", &pe::Event::MouseWheelScrollEvent::y)
		;

	py::class_<pe::Event::SizeEvent>(py_event, "_SizeEvent")
		.def_readonly("width", &pe::Event::SizeEvent::width)
		.def_readonly("hight", &pe::Event::SizeEvent::height)
		;

	///////////////////////////////////////////////////////////////////////

	m
		.def("isKeyPressed", &sf::Keyboard::isKeyPressed )
		.def("isButtonPressed", &sf::Mouse::isButtonPressed )
		.def("getMousePosition", []() { return static_cast<sf::Vector2f>( sf::Mouse::getPosition() ); } )//(sf::Vector2i(*)())& sf::Mouse::getPosition)
		.def("getMousePosition", [](const sf::Window& window) { return static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)); })//(sf::Vector2i(*)(const sf::Window&))& sf::Mouse::getPosition)
		.def("setMousePosition", [](const sf::Vector2f& vec) { sf::Mouse::setPosition(static_cast<sf::Vector2i>(vec)); })//(void(*)(const sf::Vector2i&))& sf::Mouse::setPosition)
		.def("setMousePosition", [](const sf::Vector2f& vec, const sf::Window& window) { sf::Mouse::setPosition(static_cast<sf::Vector2i>(vec), window); })//(void(*)(const sf::Vector2i&, const sf::Window&))& sf::Mouse::setPosition)
		;

	
	py_event
		.def("setHandled", &pe::Event::setHandled)
		.def("isHandled", &pe::Event::isHandled)
		.def("getType", [](pe::Event& self) { return self.type; })

		.def_readonly("size", &pe::Event::size)
		.def_readonly("key", &pe::Event::key)
		.def_readonly("mouse_move", &pe::Event::mouseMove)
		.def_readonly("mouse_button", &pe::Event::mouseButton)
		.def_readonly("mouse_wheel", &pe::Event::mouseWheel)
		.def_readonly("mouse_wheel_scroll", &pe::Event::mouseWheelScroll)

		/*
		.def("getKey", [](pe::Event& self) {return self.key.code; })
		.def("isKeyDownAlt", [](pe::Event& self) {return self.key.alt; })
		.def("isKeyDownControl", [](pe::Event& self) {return self.key.control; })
		.def("isKeyDownShift", [](pe::Event& self) {return self.key.shift; })

		.def("getButton", [](pe::Event& self) {return self.mouseButton.button; })

		.def("getWheel", [](pe::Event& self) {return self.mouseWheelScroll.wheel; })
		.def("getWheelDelta", [](sf::Event& self) {return self.mouseWheel.delta; })

		.def("getMousePosition", [](pe::Event& self)
			{
				sf::Vector2i pos;
				if (self.type == sf::Event::EventType::MouseMoved) { pos.x = self.mouseMove.x; pos.y = self.mouseMove.y; return pos; }
				if (self.type == sf::Event::EventType::MouseButtonPressed || self.type == sf::Event::EventType::MouseButtonReleased) {
					pos.x = self.mouseButton.x; pos.y = self.mouseButton.y; return pos;
				}
				if (self.type == sf::Event::EventType::MouseWheelMoved) { pos.x = self.mouseWheel.x; pos.y = self.mouseWheel.y; return pos; }
				if (self.type == sf::Event::EventType::MouseWheelScrolled) { pos.x = self.mouseWheelScroll.x; pos.y = self.mouseWheelScroll.y; return pos; }
				return pos;
			}
		)
		.def("getSize", [](pe::Event& self) {sf::Vector2i size; size.x = self.size.width; size.y = self.size.height; return size; })
		*/
		;
	
}
