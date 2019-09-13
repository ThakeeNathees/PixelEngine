#pragma once

#ifndef PE_BUILD_DLL // TODO:
	#include <SFML/Window.hpp>
	#include <SFML/Graphics.hpp>
	#include <glm.hpp>
#endif

//utils
#include "utils/FileHandler.h"
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
void pe_mainLoop( const char* project_name );

int main()
{
	register_classes();
	pe_mainLoop( TOSTRING(PE_PROJECT) );
	return 0;
}

#endif
/*************************************/

