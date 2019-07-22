#include "pepch.h"
#include "Logger.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace PE
{
	class PELogger : public Logger
	{
	public:
		PELogger(const Prop& prop):Logger(prop){
			spdlog::set_pattern("%^[%T] %n: %v%$");
			m_logger = spdlog::stdout_color_mt(m_prop.name);
		}

		virtual void log(Level level, std::string msg) const override {

		}
		virtual void log(std::string msg) const override {
			m_logger->warn(msg);
		}

	protected:
		std::shared_ptr<spdlog::logger> m_logger;

	};

	// implimentations 
	std::shared_ptr<Logger> Logger::create(const Logger::Prop& prop)
	{
		return std::make_shared<PELogger>(prop);
	}


}