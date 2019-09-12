#pragma once

#ifndef PE_BUILD_DLL // TODO:
	#include <SFML/Window.hpp>
	#include <SFML/Graphics.hpp>
	#include <glm.hpp>
#endif

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

#define STRINGIFY(x)  #x
#define TOSTRING(x) STRINGIFY(x)

/************ Entry-Point ************/
#ifdef PE_PROJECT
void register_classes();
int main()
{
	
	register_classes();
	pe::AssetsReader reader( std::string(TOSTRING(PE_PROJECT)).append(".peproj.xml").c_str() );
	reader._readPeproj();
	pe::Application::mainLoop(reader._getPeproj());
	return 0;

}
#endif
/*************************************/

