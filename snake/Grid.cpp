#include <random>
#include <chrono>
#include "Grid.h"

Grid::Grid() {}

Grid::Grid(sf::Vector2f gridSize)
{
	this->gridSize = gridSize;
	generateFood();

	// [GRAPHICS] for visuals
	offset = sf::Vector2f(55, 40);							// in pixels
	tileSize = 45;											// in pixels

	tile.setSize(sf::Vector2f(tileSize, tileSize));
	tile.setFillColor(sf::Color(72, 58, 171));
	tile.setOutlineThickness(-2.5f);
	tile.setOutlineColor(sf::Color(91, 78, 180));

	food_tile.setSize(sf::Vector2f(tileSize, tileSize));
	food_tile.setFillColor(sf::Color(182, 90, 120));
	food_tile.setOutlineThickness(-2.5f);
	food_tile.setOutlineColor(sf::Color(91, 78, 180));
	// [GRAPHICS] end
}

sf::Vector2f Grid::getSize()
{
	return gridSize;
}

int Grid::getTileSize()
{
	return tileSize;
}

sf::Vector2f Grid::getFoodPos()
{
	return foodPos;
}

void Grid::generateFood()
{
	// [MISC.] for random position generation
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 rng(seed);
	std::uniform_int_distribution<int> gen(0, std::min(gridSize.x, gridSize.y) - 1); // uniform, unbiased
	// [MISC.] end

	foodPos.x = gen(rng), foodPos.y = gen(rng);
}

sf::Vector2f Grid::getOffset()
{
	return offset;
}

sf::RectangleShape* Grid::getTile()
{
	return &tile;
}

sf::RectangleShape* Grid::getFoodTile()
{
	return &food_tile;
}