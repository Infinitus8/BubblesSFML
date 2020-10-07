#include "Bubble.hpp"

#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <cassert>

namespace ge2d
{
	Bubble::Bubble(GameDataRef data, int startCount, float minRad, float maxRad) : _data(data)
	{
		srand(time(0));
		this->_minRad = minRad;
		this->_maxRad = maxRad;

		SpawnBubbles(startCount);
	}

	Bubble::~Bubble()
	{ }

	void Bubble::Draw()
	{
		for (unsigned int i = 0; i < _bubbleShapes.size(); i++)
		{
			_data->window.draw(_bubbleShapes[i]);
		}
	}


	void Bubble::Update(float dt)
	{
		for (unsigned int i = 0; i < _bubbleShapes.size(); i++)
		{
			sf::CircleShape &shape = _bubbleShapes[i];
			sf::Vector2f scale = shape.getScale();
			
			shape.setScale(scale.x * (1 + 0.1 * dt), scale.y * (1 + 0.1 * dt));

		}
		while (true)
		{
			bool isCleared = 1;
			for (int i = 0; i < _bubbleShapes.size(); i++)
			{

				float posX = _bubbleShapes[i].getPosition().x;
				float posY = _bubbleShapes[i].getPosition().y;
				float rad = _bubbleShapes[i].getGlobalBounds().width / 2;
				std::cout << _bubbleShapes[i].getGlobalBounds().width / 2 << std::endl;
				if (posX < rad || _data->window.getSize().x - posX < rad
					|| posY < rad || _data->window.getSize().y - posY < rad)
				{
					_bubbleShapes.erase(_bubbleShapes.begin() + i);
					isCleared = 0;
					break;
				}
			}
			if (isCleared)
			{
				break;
			}
		}

		while (true)
		{
			int isMerged = 1;
			int iCount = _bubbleShapes.size();
			if (_bubbleShapes.size() == 0)
			{
				iCount = 1;
			}
			for (int i = 0; i < iCount - 1; i++)
			{
				for (int j = i + 1; j < iCount; j++)
				{
					if (CirclesCollision(_bubbleShapes[i], _bubbleShapes[j]))
					{
						sf::Vector2f disVec(_bubbleShapes[j].getPosition().x - _bubbleShapes[i].getPosition().x,
							_bubbleShapes[j].getPosition().y - _bubbleShapes[i].getPosition().y);
						float dist = sqrt(disVec.x * disVec.x + disVec.y * disVec.y);
						float rad1 = _bubbleShapes[i].getGlobalBounds().width / 2;
						float rad2 = _bubbleShapes[j].getGlobalBounds().width / 2;
						float val = rad1 / dist;
						float posX = _bubbleShapes[i].getPosition().x;
						float posY = _bubbleShapes[i].getPosition().y;
						_bubbleShapes.erase(_bubbleShapes.begin() + i);
						_bubbleShapes.erase(_bubbleShapes.begin() + j - 1);
						float colPointX = posX + val * disVec.x;
						float colPointY = posY + val * disVec.y;
						SpawnMergedBubble(colPointX, colPointY, sqrt(rad1 * rad1 + rad2 * rad2));
						isMerged = 0;
						break;
					}
				}
				if (!isMerged)
				{
					break;
				}
			}
			if (isMerged)
			{
				break;
			}

		}
		

	}

	int Bubble::RandInt(int min, int max)
	{
		return rand() % (max - min) + min + 1;
	}

	float Bubble::RandFloat(float min, float max) 
	{
		return (min + 1) + (((float)rand()) / (float)RAND_MAX) * (max - (min + 1));
	}

	sf::Vector2f Bubble::GenerateUnoccupiedPos(float rad)
	{
		float minX = rad;
		float maxX = _data->window.getSize().x - rad;
		float minY = rad;
		float maxY = _data->window.getSize().y - rad;
		srand(time(0));
		int occupied = 1;
		float posX = 0;
		float posY = 0;
		while (occupied) 
		{
			occupied = 0;
			posX = RandFloat(minX, maxX);
			posY = RandFloat(minY, maxY);
			std::cout << rad << std::endl;
			std::cout << minX << " " << maxX << " " << minY << " " << maxY << " " << posX << " " << posY << std::endl;
			for (unsigned int i = 0; i < _bubbleShapes.size(); i++)
			{
				sf::CircleShape probCirc;
				probCirc.setRadius(rad);
				probCirc.setOrigin(probCirc.getLocalBounds().width / 2,
					probCirc.getLocalBounds().height / 2);
				probCirc.setPosition(posX, posY);
				if (CirclesCollision(probCirc, _bubbleShapes[i]))
				{
					occupied = 1;
					continue;
				}
			}
		}
		

		
		return sf::Vector2f(posX, posY);
	}


	void Bubble::SpawnMergedBubble(float posX, float posY, float rad)
	{
		sf::CircleShape bubbleShape;
		bubbleShape.setRadius(rad);
		bubbleShape.setOrigin(bubbleShape.getLocalBounds().width / 2,
			bubbleShape.getLocalBounds().height / 2);
		bubbleShape.setPosition(posX, posY);
		_bubbleShapes.push_back(bubbleShape);
	}

	void Bubble::SpawnBubbles(int count)
	{
		for (unsigned int i = 0; i < count; i++)
		{
			float rad = RandFloat(_minRad, _maxRad);
			sf::Vector2f pos = GenerateUnoccupiedPos(rad);
			sf::CircleShape bubbleShape;
			bubbleShape.setRadius(rad);
			bubbleShape.setOrigin(bubbleShape.getLocalBounds().width / 2, 
				bubbleShape.getLocalBounds().height / 2);
			bubbleShape.setPosition(pos.x, pos.y);
			_bubbleShapes.push_back(bubbleShape);
		}
	}

	void Bubble::CircleCollision(sf::CircleShape obj)
	{
		
	}

	bool Bubble::CirclesCollision(sf::CircleShape obj1, sf::CircleShape obj2)
	{
		sf::Vector2f disVec(obj2.getPosition().x - obj1.getPosition().x, obj2.getPosition().y - obj1.getPosition().y);
		float distance = sqrt(disVec.x * disVec.x + disVec.y * disVec.y);
		float rad1 = obj1.getGlobalBounds().width / 2;
		float rad2 = obj2.getGlobalBounds().width / 2;
		if (distance <= (rad1 + rad2))
		{
			return true;
		}
		return false;
	}
}