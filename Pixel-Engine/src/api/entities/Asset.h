#pragma once
#include "..//core.h"


namespace pe
{
	class PIXEL_ENGINE_API Asset
	{
	public:
		enum class Type
		{
			/*name    id pre-val*/
			Texture		= 00000, 
			Font		= 10000, 
			Area		= 20000, 
			Sprite		= 30000, 
			Background	= 40000, 
			Animation	= 50000,  
			Object		= 60000,
			Scene		= 70000,
		};

		virtual int getId() const =0;
		virtual const std::string& getName() const =0;
		virtual void setName(const std::string& name) = 0;

		virtual Type getType() const = 0;
	};
}