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


#include <iostream>
#define print(x) std::cout << x << std::endl;

#define __CLASS__ (typeid(*this).name()+6)
#define BIT(X) (1 << X)