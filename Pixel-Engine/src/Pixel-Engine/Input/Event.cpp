#include "pepch.h"
#include "Event.h"

#include "WindowEvent.h"
#include "MouseEvent.h"


namespace PE
{

	bool Event::isPressed() const {
		PE_ERROR("isPressed() method only be called from KeyEvent and MouseEvents events!");
		PE_INFO("check the event before calling isPressed()\n"
			"if ( (event.getType() & PE::Event::KeyEvent) || (event.getType() & PE::Event::MouseEvent) ){ event.isPressed(); }\n"
			"		--OR--\n"
			"if (event.getType() == PE::Event::MOUSE_RIGHT ) { event.isPressed(); }"
			"if (event.getType() == PE::Event::MOUSE_LEFT  ) { event.isPressed(); }"
		);
		PE_ERROR_PAUSE();
		return Input::KEY_UNKNOWN;
	}

	Input::Key Event::getKey() const {
		PE_ERROR("getKey() method only be called from KeyEvent events!");
		PE_INFO("check if event is KeyEvent before calling getKey()\n"
				"if ( event.getType() & PE::Event::KeyEvent ){ event.getKey(); }\n"
				"		--OR--\n"
				"if (event.getType() == PE::Event::KEY_PRESSED ) { event.getKey(); }\n"   
				"if (event.getType() == PE::Event::KEY_RELEASED ) { event.getKey(); }"   
				);
		PE_ERROR_PAUSE();
		return Input::KEY_UNKNOWN;
	}
	
	Input::Button Event::getButton() const {
		PE_ERROR("getButton() method only be called from Mouse events!");
		PE_INFO("check if event is MouseEvent before calling getButton()\n"
				"if ( event.getType() & PE::Event::MouseEvent ){ event.getButton(); }\n"
				"		--OR--\n"
				"if (event.getType() == PE::Event::MOUSE_PRESSED ) { event.getButton(); }\n"
				"if (event.getType() == PE::Event::MOUSE_RELEASED ) { event.getButton(); }\n"
				"if (event.getType() == PE::Event::MOUSE_MOTION ) { event.getButton(); }"
				);
		PE_ERROR_PAUSE();
		return Input::BUTTON_UNKNOWN;
	}
	
	vec2 Event::getPosition() const {
		PE_ERROR("getPosition() method only be called from MOUSE_MOTION events!");
		PE_INFO("check if event is MOUSE_MOTION before calling getButton()\n"
			"if ( event.getType() == PE::Event::MOUSE_MOTION ){ event.getButton(); }\n"
			"		--OR--\n"
			"use PE::Input::getMousePosition() method to get the mouse position\n"
			
		);
		PE_ERROR_PAUSE();
		return vec2(.0f,.0f);
	}

	vec2 Event::getSize() const {
		PE_ERROR("getSize() method only be called from RESIZED events!");
		PE_INFO("check if event is RESIZED before calling getSize()\n"
			"if ( event.getType() == PE::Event::RESIZED ){ event.getSize(); }\n"
		);
		PE_ERROR_PAUSE();
		return vec2(-1.f,-1.f);
	}

	vec2 WindowEvent::getSizeError() const {
		PE_ERROR("getSize() method only be called from RESIZED events!");
		PE_INFO("check if event is RESIZED before calling getSize()\n"
			"if ( event.getType() == PE::Event::RESIZED ){ event.getSize(); }\n"
		);
		PE_ERROR_PAUSE();
		return vec2(-1.f, -1.f);
	}

	vec2 MouseEvent::getPositionError() const
	{
		PE_ERROR("getPosition() method only be called from MOUSE_MOTION events!");
		PE_INFO("check if event is MOUSE_MOTION before calling getButton()\n"
			"if ( event.getType() == PE::Event::MOUSE_MOTION ){ event.getButton(); }\n"
			"		--OR--\n"
			"use PE::Input::getMousePosition() method to get the mouse position\n"

		);
		PE_ERROR_PAUSE();
		return vec2(.0f, .0f);
	}
}