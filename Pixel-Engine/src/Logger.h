#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#define PE_ERROR_PAUSE(...) while(true)

#define PE_SUCCESS(...)	::pe::Logger::getLogger()->info(__VA_ARGS__)
#define PE_INFO(...)    std::cout << __VA_ARGS__ << std::endl
#define PE_WARN(...)	::pe::Logger::getLogger()->warn(__VA_ARGS__)
#define PE_ERROR(...)	::pe::Logger::getLogger()->error(__VA_ARGS__);PE_ERROR_PAUSE();
#define PE_FATAL(...)	::pe::Logger::getLogger()->critical(__VA_ARGS__);PE_ERROR_PAUSE();

#ifdef PE_ENABLE_ASSERTS
	#define PE_ASSERT(x, ...) { if(!x){ ::pe::Logger::getLogger()->error(__VA_ARGS__); __debugbreak(); } }
#else
	#define PE_ASSERT(x, ...)
#endif

namespace pe
{

	class Logger
	{
	public:
		static void Init();
		static std::shared_ptr<spdlog::logger> getLogger();

	private:
		static std::shared_ptr < spdlog::logger > s_logger;

	};

}

