#pragma once

#include <memory>
#include <string>

#include <SFML/Graphics.hpp>
#include "StateMachine.hpp"


namespace ge2d
{
	struct GameData
	{
		StateMachine machine;
		sf::RenderWindow window;

	};

	typedef std::shared_ptr<GameData> GameDataRef;

	class Game
	{
	public:
		Game(int width, int height, int bCount, float minRad, float maxRad, std::string title);

	private:
		const float dt = 1.0f / 60.0f;
		sf::Clock _clock;

		GameDataRef _data = std::make_shared<GameData>();

		void Run();
	};
}