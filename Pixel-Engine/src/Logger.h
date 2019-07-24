#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#define PE_ERROR_PAUSE(...) while(true)

#define PE_SUCCESS(...)	::PE::Logger::getLogger()->info(__VA_ARGS__)
#define PE_INFO(...)    std::cout << __VA_ARGS__ << std::endl
#define PE_WARN(...)	::PE::Logger::getLogger()->warn(__VA_ARGS__)
#define PE_ERROR(...)	::PE::Logger::getLogger()->error(__VA_ARGS__)
#define PE_FATAL(...)	::PE::Logger::getLogger()->critical(__VA_ARGS__)

#ifdef PE_ENABLE_ASSERTS
	#define PE_ASSERT(x, ...) { if(!x){ ::PE::Logger::getLogger()->error(__VA_ARGS__); __debugbreak(); } }
#else
	#define PE_ASSERT(x, ...)
#endif

namespace PE
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

