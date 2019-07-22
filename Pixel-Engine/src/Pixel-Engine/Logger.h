#pragma once

#include "Core.h"


namespace PE
{

	class PIXEL_ENGINE_API Logger
	{
	public:

		enum Level
		{
			L_SUCCESS	= -1,
			L_INFO		=  0,
			L_WARN		=  1,
			L_ERROR		=  2
		};
		struct Prop
		{
			std::string name;
			Level level;
		};

		static std::shared_ptr<Logger> create(const Prop& prop = {"Pixel-Engine", Level::L_INFO});

		Logger(const Prop& prop);
		~Logger();
		virtual void Init() = 0;

		virtual void log(std::string msg) const =0;
		virtual void log(Level level, std::string msg) const = 0;

		// setter
		inline void setLevel(Level level) { m_prop.level = level; }

		// getter
		inline Level getLevel() const { return m_prop.level; }

	protected:
		Prop m_prop;
		std::stringstream m_string_stream;
	};

	
	inline Logger::Logger(const Prop& prop) : m_prop(prop){ }
	inline Logger::~Logger() {}




	



	
	
	
	
	
	
	
	
	

}

