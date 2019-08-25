#pragma once
#include "..//core.h"

#include "tinyxml2.h"

namespace pe
{
	class PIXEL_ENGINE_API XmlFile
	{
	public:
		XmlFile();

	private:
		tinyxml2::XMLDocument m_doc;
	};
}
