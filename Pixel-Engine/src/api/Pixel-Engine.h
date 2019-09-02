#pragma once


//utils
#include "utils/io_utils.h"
#include "utils/math_utils.h"
#include "utils/AssetsReader.h"
#include "utils/AssetsWriter.h"

#include "Application.h"
#include "Scene.h"

// entities
#include "entities/Sprite.h"
#include "entities/Object.h"
#include "entities/Background.h"
#include "entities/Area.h"
#include "entities/Signal.h"
#include "entities/Timer.h"
#include "entities/Animation.h"

#include "misc/Event.h"
#include "misc/Texture.h"
#include "misc/Font.h"
#include "misc/Drawable.h"

/************ Entry-Point ************/
#ifndef PE_NO_MAIN
void register_classes();
int main()
{
	pe::Application::test();
	register_classes();

	pe::AssetsReader reader("SandBox.peproj.xml");
	reader._readPeproj();
	pe::Application app( reader._getPeproj() );
	
	app.update();

	return 0;
}
#endif
/*************************************/

