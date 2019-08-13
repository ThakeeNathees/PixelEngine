#pragma once

#ifdef PE_PLATFORM_WINDOWS
	#ifdef PE_BUILD_DLL
		#define PIXEL_ENGINE_API __declspec(dllexport)
	#else
		#define PIXEL_ENGINE_API __declspec(dllimport)
	#endif
#else
	#error Pixel-Engine only supports Windows!
#endif 


// for debug
#include <iostream>
#define print(x) std::cout << x << std::endl;

#define PE_ASSERT(x) if(!x) __debugbreak()

#define __CLASS__ (typeid(*this).name()+6)