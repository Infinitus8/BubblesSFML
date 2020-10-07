#pragma once

#include <iostream>
#include <cassert>
#include "GameState.hpp"




namespace ge2d
{
	GameState::GameState(GameDataRef data, int bCount, float minRad, float maxRad) : _data(data)
	{
		this->_bCount = bCount;
		this->_minRad = minRad;
		this->_maxRad = maxRad;
	}

	void GameState::Init()
	{
		bubble = new Bubble(_data, _bCount, _minRad, _maxRad);
	}


	void GameState::Update(float dt)
	{
		sf::Event event;

		while (_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				_data->window.close();
			}
		}

		bubble->Update(dt);
	}

	void GameState::Draw(float dt)
	{
		_data->window.clear();

		bubble->Draw();

		_data->window.display();
	}

	
}