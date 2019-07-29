#pragma once
#include "core.h"


namespace pe
{
	class PIXEL_ENGINE_API Game
	{
	public:
		static std::shared_ptr<Game> getInstance();

	private:
		Game();
	};

}