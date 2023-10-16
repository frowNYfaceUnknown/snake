#include "Grid.h"
#include <random>
#include <chrono>

Grid::Grid() {}

Grid::Grid(sf::Vector2f gridSize)
{
	this->gridSize = gridSize;
	generateFood();

	// for visuals
	offset = sf::Vector2f(55, 22.5);		// in pixels
	tileSize = 45;							// in pixels

	tile.setSize(sf::Vector2f(tileSize, tileSize));
	tile.setFillColor(sf::Color(249, 167, 62));
	tile.setOutlineThickness(-2.5f);
	tile.setOutlineColor(sf::Color(246, 253, 195));

	food_tile.setSize(sf::Vector2f(tileSize, tileSize));
	food_tile.setFillColor(sf::Color(191, 33, 47));
	food_tile.setOutlineThickness(-2.5f);
	food_tile.setOutlineColor(sf::Color(246, 253, 195));
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