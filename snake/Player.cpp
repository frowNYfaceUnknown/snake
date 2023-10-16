#include "Player.h"

Player::Player(Grid* grid, sf::Vector2f pos)
{
	alive = true;
	length = 1;
	this->grid = grid;
	body.push_front(pos);
	currDir = sf::Vector2f(1, 0);
	speed = 5;												// tiles per second

	// for visuals
	snake_tile.setSize(sf::Vector2f(grid->getTileSize(), grid->getTileSize()));
	snake_tile.setFillColor(sf::Color(39, 179, 118));
	snake_tile.setOutlineThickness(-2.5f);
	snake_tile.setOutlineColor(sf::Color(246, 253, 195));
}

void Player::move()
{
	if (alive)
	{
		sf::Vector2f bodyEnd = body.back();					// [GROW] stores the value of the tail before moving

		// [MOVESNAKE] moves the snake overall by 1 tile

		if (body.size() > 1)
		{
			std::list<sf::Vector2f>::iterator it;
			for (it = --body.end(); it != body.begin(); --it)
			{
				it->x = ((--it)++)->x;
				it->y = ((--it)++)->y;
			}
		}
		body.front() += currDir;

		// [MOVESNAKE] end

		if (body.front() == grid->getFoodPos())				// [GROW] appends it only if the snake ate the food
		{
			body.push_back(bodyEnd);
			grid->generateFood();
		}

		// [KILLSNAKE] if the snake moves out of bounds or into itself, kill the snake

		if (body.front().x >= grid->getSize().x || body.front().x < 0 || body.front().y >= grid->getSize().y || body.front().y < 0)
			alive = false;

		std::list<sf::Vector2f>::iterator it;
		for (it = ++body.begin(); it != body.end(); ++it)
		{
			if ((*it) == body.front())
				alive = false;
		}

		// [KILLSNAKE] end
	}
}

void Player::changeDir(sf::Vector2f direction)
{
	if ((direction.x == -(this->currDir.x) && direction.x != 0) || (direction.y == -(this->currDir.y) && direction.y != 0))
		this->alive = false;
	else if (alive)
		this->currDir = direction;
}

sf::Vector2f Player::getPos()
{
	return this->body.front();
}

double Player::getSpeed()
{
	return speed;
}

bool Player::isAlive()
{
	return this->alive;
}

sf::RectangleShape* Player::getTile()
{
	return &snake_tile;
}