#include "pepch.h"
#include "Event.h"



namespace PE
{
	Input Event::getKey() const {
		PE_ERROR("getKey() method only be called from KeyEvent events!");
		PE_INFO("check if event is KeyEvent before calling getKey()\n"
			"if ( event.getType() & PE::Event::KeyEvent ){ event.getKey(); }\n"
			"		--OR--\n"
			"if (event.getType() == PE::Event::KEY_PRESSED ) { event.getKey(); }\n"   
			"if (event.getType() == PE::Event::KEY_RELEASED ) { event.getKey(); }"   
			"" );
		PE_ERROR_PAUSE();
		return KEY_UNKNOWN;
	}
	
	Input Event::getButton() const {
		PE_ERROR("getButton() method only be called from Mouse events! ", "check event.getType() == PE::Event::MouseEvent");
		return KEY_UNKNOWN;
	}
	
	vect2 Event::getPosition() const {
		PE_ERROR("getPosition() method only be called from Mouse events!");
		return vect2(.0f,.0f);
	}



}