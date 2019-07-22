#pragma once

#include "Core.h"


namespace PE
{

	class PIXEL_ENGINE_API Logger
	{
	public:
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
	};

	
	inline Logger::Logger(const Prop& prop) : m_prop(prop){ }
	inline Logger::~Logger() {}




	



	
	
	
	
	
	
	
	
	

}

