#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"


#ifdef PE_ENABLE_ASSERTS
	#define PE_ASSERT(x, PE_ASSERT_MSG) { if(!x){ ::PE::Logger::logAssert(PE_ASSERT_MSG); __debugbreak(); } }
#else
	#define PE_ASSERT(x, ...)
#endif


namespace PE
{

	class Logger
	{
	public:
		static void Init();

	private:
		static std::shared_ptr < spdlog::logger > s_logger;

		//old
	public
		// enums and structs
		enum Level
		{
			L_SUCCESS	= -1,
			L_INFO		=  0,
			L_WARN		=  1,
			L_ERROR		=  2,
			L_FATAL		=  3,
		};
		
		struct Prop
		{
			std::string name;
			Level level;
			bool is_logging;
		};

		// static field constructor init and distructor
		static std::shared_ptr<Logger> create(const Prop& prop = {"Pixel-Engine", Level::L_SUCCESS, true});
		static void logAssert(const std::string& assert_msg);
		Logger(const Prop& prop);
		~Logger();

		// methods
		virtual void log( const Level& level, const std::string& msg) const = 0;
		virtual void info(const std::string& msg) const = 0;
		virtual void warn(const std::string& msg) const = 0;
		virtual void error(const std::string& msg) const = 0;
		virtual void fatal(const std::string& msg) const = 0;
		virtual void success(const std::string& msg) const = 0;

		// setter
		inline void setLevel(const Level& level) { m_prop.level = level; }

		// getter
		inline Level getLevel() const { return m_prop.level; }

	protected:
		Prop m_prop;
		std::stringstream m_string_stream;
		static std::shared_ptr<Logger> m_assert_logger;
	};

	
	inline Logger::Logger(const Prop& prop) : m_prop(prop){ }
	inline Logger::~Logger() {}




	



	
	
	
	
	
	
	
	
	

}

