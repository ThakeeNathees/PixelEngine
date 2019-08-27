#pragma once
#include "..//core.h"


namespace pe
{
	class PIXEL_ENGINE_API Asset
	{
	public:
		virtual int getId() const =0;
		virtual const std::string& getName() const =0;
		virtual void setName(const std::string& name) = 0;
	};
}