#include "Game.hpp"
#include "GameState.hpp"

#include <stdlib.h>
#include <time.h>

namespace ge2d
{
	Game::Game(int width, int height, int bCount, float minRad, float maxRad, std::string title)
	{
		srand(time(NULL));

		_data->window.create(sf::VideoMode(width, height),
			title, sf::Style::Close | sf::Style::Titlebar);
		_data->machine.AddState(StateRef(new GameState(this->_data, bCount, minRad, maxRad)));

		this->Run();
	}

	void Game::Run()
	{
		float newTime, frameTime, interpolation;

		float currentTime = this->_clock.getElapsedTime().asSeconds();
		float accumulator = 0.0f;

		while (this->_data->window.isOpen())
		{
			this->_data->machine.ProcessStateChanges();

			newTime = this->_clock.getElapsedTime().asSeconds();
			frameTime = newTime - currentTime;

			if (frameTime > 0.25f)
			{
				frameTime = 0.25;
			}

			currentTime = newTime;
			accumulator += frameTime;

			while (accumulator >= dt)
			{
				this->_data->machine.GetActiveState()->Update(dt);

				accumulator -= dt;
			}

			interpolation = accumulator / dt;
			this->_data->machine.GetActiveState()->Draw(interpolation);
		}
	}
} 