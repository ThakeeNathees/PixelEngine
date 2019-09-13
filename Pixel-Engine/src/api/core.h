#pragma once

#ifdef _WIN32

	#define NOMINMAX
	#include <Windows.h>

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
#define PE_PRINT(x) std::cout << x << std::endl;
#define PE_LOG(x) std::cout << "[pe] " << x << std::endl
#define PE_ASSERT(x) if(!x) __debugbreak()
