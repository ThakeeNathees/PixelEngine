#include "pepch.h"
#include "Logger.h"


namespace pe
{

	std::shared_ptr<spdlog::logger> Logger::s_logger;

	void Logger::Init()
	{
		spdlog::set_pattern("%^[%n]: %v%$");
		s_logger = spdlog::stdout_color_mt("Pixel-Engine");
		s_logger->set_level(spdlog::level::trace);
	}

	std::shared_ptr<spdlog::logger> Logger::getLogger()
	{
		return s_logger;
	}

}

