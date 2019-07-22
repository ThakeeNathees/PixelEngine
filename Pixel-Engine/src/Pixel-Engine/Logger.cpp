#include "pepch.h"
#include "Logger.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace PE
{
	class PELogger : public Logger
	{
	public:
		// constructor init and distructors
		PELogger(const Prop& prop):Logger(prop){
			spdlog::set_pattern("%^[%n]: %v%$");
			m_logger = spdlog::stdout_color_mt(m_prop.name);
		}

		// methods
		virtual void success(const std::string& msg) const override  { if (m_prop.level <= Logger::Level::L_SUCCESS && m_prop.is_logging) m_logger->info(msg); }
		virtual void info(const std::string& msg) const override     { if (m_prop.level <= Logger::Level::L_INFO && m_prop.is_logging) std::cout << "["<< m_prop.name <<"]: " << msg << std::endl; }
		virtual void warn(const std::string& msg) const override     { if (m_prop.level <= Logger::Level::L_WARN && m_prop.is_logging) m_logger->warn(msg); }
		virtual void error(const std::string& msg) const override    { if (m_prop.level <= Logger::Level::L_ERROR && m_prop.is_logging) m_logger->error(msg); }
		virtual void fatal(const std::string& msg) const override    { if (m_prop.level <= Logger::Level::L_FATAL && m_prop.is_logging)m_logger->critical(msg); }
		virtual void log(const Level& level, const std::string& msg) const override {
			switch (level) {
			case Level::L_SUCCESS:	success(msg); break;
			case Level::L_INFO:		info(msg); break;
			case Level::L_WARN:		warn(msg); break;
			case Level::L_ERROR:	error(msg); break;
			case Level::L_FATAL:	fatal(msg); break;
			}
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