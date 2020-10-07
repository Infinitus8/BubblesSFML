#include <iostream>
#include <SFML\Graphics.hpp>

#include "Game.hpp"

int main()
{

	int width, height, bCount;
	float minRad, maxRad;
	std::cout << "RectWidth = ";
	std::cin >> width;
	std::cout << "RectHeight = ";
	std::cin >> height;
	std::cout << "ObjectCount = ";
	std::cin >> bCount;
	std::cout << "ObjectMinRadius = ";
	std::cin >> minRad;
	std::cout << "ObjectMaxRadius = ";
	std::cin >> maxRad;
	ge2d::Game(width, height, bCount, minRad, maxRad, "BubblesSFML");

	return 0;
}