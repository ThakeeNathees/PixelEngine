#include "pch.h"
#include "Game.h"

namespace pe
{
	Game::Game() {}

	std::shared_ptr<Game> Game::getInstance()
	{
		static std::shared_ptr<Game> s_game(new Game);
		return s_game;
	}
}