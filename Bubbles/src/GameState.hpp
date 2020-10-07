#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

#include "Bubble.hpp"

namespace ge2d
{
	class GameState : public State
	{
	public:
		GameState(GameDataRef data, int bCount, float minRad, float maxRad);

		void Init();

		void Update(float dt);
		void Draw(float dt);


	private:
		GameDataRef _data;

		Bubble *bubble;

		int _bCount;
		float _minRad, _maxRad;


		sf::Clock _clock;

	};
}