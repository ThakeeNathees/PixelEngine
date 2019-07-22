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

// move this to Logger.h
#ifdef PE_ENABLE_ASSERTS
#define PE_ASSERT(x, PE_ASSERT_MSG) { if(!x){ ::PE::Logger::logAssert(PE_ASSERT_MSG); __debugbreak(); } }
#else
#define PE_ASSERT(x, ...)
#endif

#define __CLASS__ (typeid(*this).name()+6)
