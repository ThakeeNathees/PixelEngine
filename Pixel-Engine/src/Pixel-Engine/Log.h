#pragma once

#include <memory>
#include "Core.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

namespace PE
{

	class PIXEL_ENGINE_API Log
	{
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return s_core_logger; }
		inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return s_client_logger; }
	private:
		static std::shared_ptr<spdlog::logger> s_core_logger;
		static std::shared_ptr<spdlog::logger> s_client_logger;

	};

}

// core log macros
#define PE_CORE_TRACE(...)	::PE::Log::getCoreLogger()->trace(__VA_ARGS__)
#define PE_CORE_INFO(...)	::PE::Log::getCoreLogger()->info(__VA_ARGS__)
#define PE_CORE_WARN(...)	::PE::Log::getCoreLogger()->warn(__VA_ARGS__)
#define PE_CORE_ERROR(...)	::PE::Log::getCoreLogger()->error(__VA_ARGS__)
//#define PE_CORE_FATAL(...)	::PE::Log::getCoreLogger()->fatal(__VA_ARGS__)


// client log macros
#define PE_TRACE(...)	::PE::Log::getClientLogger()->trace(__VA_ARGS__)
#define PE_INFO(...)	::PE::Log::getClientLogger()->info(__VA_ARGS__)
#define PE_WARN(...)	::PE::Log::getClientLogger()->warn(__VA_ARGS__)
#define PE_ERROR(...)	::PE::Log::getClientLogger()->error(__VA_ARGS__)
//#define PE_FATAL(...)	::PE::Log::getClientLogger()->fatal(__VA_ARGS__)