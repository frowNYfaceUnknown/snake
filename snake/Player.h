#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Grid.h"

class Player
{
public:
	std::list<sf::Vector2f> body; // [MOVE-FROM] here
public:
	Player(Grid* grid, sf::Vector2f pos);
	void move();
	void changeDir(sf::Vector2f direction);
	bool isAlive();
	sf::Vector2f getPos();
	double getSpeed();
	sf::RectangleShape* getTile();
	int getLength();
private:
	bool alive;
	// [MOVE-TO] shift body here
	sf::Vector2f currDir;
	double speed;
	int length;
	Grid* grid;

	// for visuals
	sf::RectangleShape snake_tile;
};