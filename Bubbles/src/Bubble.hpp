#pragma once

#include <SFML/Graphics.hpp>

#include "Game.hpp"
#include <vector>

namespace ge2d
{
	class Bubble
	{
	public:
		Bubble(GameDataRef data, int startCount, float minRad, float maxRad);
		~Bubble();

		void Draw();

		void Update(float dt);

		int RandInt(int min, int max);

		float RandFloat(float min, float max);

		sf::Vector2f GenerateUnoccupiedPos(float rad);

		void CircleCollision(sf::CircleShape obj);
		bool CirclesCollision(sf::CircleShape obj1, sf::CircleShape obj2);

		void SpawnMergedBubble(float posX, float posY, float rad);
		void SpawnBubbles(int count);

	private:
		GameDataRef _data;
		std::vector<sf::CircleShape> _bubbleShapes;


		float _minRad, _maxRad;

		sf::Clock _clock;
	};
}
