#pragma once
#include <SFML/Graphics.hpp>

class Grid
{
public:
	Grid();
	Grid(sf::Vector2f gridSize);
	sf::Vector2f getSize();
	sf::Vector2f getFoodPos();
	int getTileSize();
	void generateFood();

	// for visuals
	sf::Vector2f getOffset();
	sf::RectangleShape* getTile();
	sf::RectangleShape* getFoodTile();
private:
	sf::Vector2f gridSize;
	sf::Vector2f foodPos;

	// for visuals
	sf::Vector2f offset;
	int tileSize;
	sf::RectangleShape tile;
	sf::RectangleShape food_tile;
};