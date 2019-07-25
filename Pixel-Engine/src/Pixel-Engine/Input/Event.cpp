#include "pepch.h"
#include "Event.h"

#include "WindowEvent.h"
#include "MouseEvent.h"


namespace pe
{
	std::string Event::toString()
	{
		switch (m_type) {
		case Event::CLOSED:			return "Event::CLOSED";			break;
		case Event::RESIZED:		return "Event::RESIZED";		break;
		case Event::LOST_FOCUS:		return "Event::LOST_FOCUS";		break;
		case Event::GAINED_FOCUSED: return "Event::GAINED_FOCUSED"; break;
		case Event::MOUSE_ENTERED:	return "Event::MOUSE_ENTERED";	break;
		case Event::MOUSE_LEFT:		return "Event::MOUSE_LEFT";		break;
		case Event::KEY_PRESSED:	return "Event::KEY_PRESSED";	break;
		case Event::KEY_RELEASED:	return "Event::KEY_RELEASED";	break;
		case Event::MOUSE_PRESSED:	return "Event::MOUSE_PRESSED";	break;
		case Event::MOUSE_RELEASED: return "Event::MOUSE_RELEASED"; break;
		case Event::MOUSE_WHEEL:	return "Event::MOUSE_WHEEL";	break;
		case Event::MOUSE_MOTION:	return "Event::MOUSE_MOTION";	break;
		case Event::NONE:
		default:
			return "Event::NONE"; break;

		}
	}

	bool Event::isPressed() const {
		PE_ERROR("isPressed() method only be called from KeyEvent and MouseEvents events!");
		PE_INFO("check the event before calling isPressed()\n"
			"if ( (event.getType() & pe::Event::KeyEvent) || (event.getType() & pe::Event::MouseEvent) ){ event.isPressed(); }\n"
			"		--OR--\n"
			"if (event.getType() == pe::Event::MOUSE_RIGHT ) { event.isPressed(); }"
			"if (event.getType() == pe::Event::MOUSE_LEFT  ) { event.isPressed(); }"
		);
		PE_ERROR_PAUSE();
		return Input::KEY_UNKNOWN;
	}

	Input::Key Event::getKey() const {
		PE_ERROR("getKey() method only be called from KeyEvent events!");
		PE_INFO("check if event is KeyEvent before calling getKey()\n"
				"if ( event.getType() & pe::Event::KeyEvent ){ event.getKey(); }\n"
				"		--OR--\n"
				"if (event.getType() == pe::Event::KEY_PRESSED ) { event.getKey(); }\n"   
				"if (event.getType() == pe::Event::KEY_RELEASED ) { event.getKey(); }"   
				);
		PE_ERROR_PAUSE();
		return Input::KEY_UNKNOWN;
	}
	
	Input::Button Event::getButton() const {
		PE_ERROR("getButton() method only be called from Mouse events!");
		PE_INFO("check if event is MouseEvent before calling getButton()\n"
				"if ( event.getType() & pe::Event::MouseEvent ){ event.getButton(); }\n"
				"		--OR--\n"
				"if (event.getType() == pe::Event::MOUSE_PRESSED ) { event.getButton(); }\n"
				"if (event.getType() == pe::Event::MOUSE_RELEASED ) { event.getButton(); }\n"
				"if (event.getType() == pe::Event::MOUSE_MOTION ) { event.getButton(); }"
				);
		PE_ERROR_PAUSE();
		return Input::BUTTON_UNKNOWN;
	}
	
	vec2 Event::getPosition() const {
		PE_ERROR("getPosition() method only be called from MOUSE_MOTION events!");
		PE_INFO("check if event is MOUSE_MOTION before calling getButton()\n"
			"if ( event.getType() == pe::Event::MOUSE_MOTION ){ event.getButton(); }\n"
			"		--OR--\n"
			"use pe::Input::getMousePosition() method to get the mouse position\n"
			
		);
		PE_ERROR_PAUSE();
		return vec2(.0f,.0f);
	}

	vec2 Event::getSize() const {
		PE_ERROR("getSize() method only be called from RESIZED event!");
		PE_INFO("check if event is RESIZED before calling getSize()\n"
			"if ( event.getType() == pe::Event::RESIZED ){ event.getSize(); }\n"
		);
		PE_ERROR_PAUSE();
		return vec2(-1.f,-1.f);
	}

	float Event::getDelta() const {
		PE_ERROR("getDelta() method only be called from MOUSE_WHEEL event!");
		PE_INFO("check if event is MOUSE_WHEEL before calling getDelta()\n"
			"if ( event.getType() == pe::Event::MOUSE_WHEEL ){ event.getSize(); }\n"
		);
		PE_ERROR_PAUSE();
		return .0f;
	}

	float MouseEvent::getDeltaError() const {
		PE_ERROR("getDelta() method only be called from MOUSE_WHEEL event!");
		PE_INFO("check if event is MOUSE_WHEEL before calling getDelta()\n"
			"if ( event.getType() == pe::Event::MOUSE_WHEEL ){ event.getSize(); }\n"
		);
		PE_ERROR_PAUSE();
		return .0f;
	}


	vec2 WindowEvent::getSizeError() const {
		PE_ERROR("getSize() method only be called from RESIZED event!");
		PE_INFO("check if event is RESIZED before calling getSize()\n"
			"if ( event.getType() == pe::Event::RESIZED ){ event.getSize(); }\n"
		);
		PE_ERROR_PAUSE();
		return vec2(-1.f, -1.f);
	}

	vec2 MouseEvent::getPositionError() const
	{
		PE_ERROR("getPosition() method only be called from MOUSE_MOTION events!");
		PE_INFO("check if event is MOUSE_MOTION before calling getButton()\n"
			"if ( event.getType() == pe::Event::MOUSE_MOTION ){ event.getButton(); }\n"
			"		--OR--\n"
			"use pe::Input::getMousePosition() method to get the mouse position\n"

		);
		PE_ERROR_PAUSE();
		return vec2(.0f, .0f);
	}
}