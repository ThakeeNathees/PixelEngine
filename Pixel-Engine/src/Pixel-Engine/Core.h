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

#ifdef PE_ENABLE_ASSERTS
	#define PE_ASSERT(x, ...) { if(!x){ PE_ERROR("Assertion Failed: {0}", __VA_ARGS__);  __debugbread(); } }
	#define PE_CORE_ASSERT(x, ...) { if(!x){ PE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__);  __debugbread(); } }

#else
	#define PE_ASSERT(x, ...)
	#define PE_CORE_ASSERT(x, ...)
#endif

#define __CLASS__ (typeid(*this).name()+6)

#define BIT(x)  (1 << x)