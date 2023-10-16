#include <iostream>
#include "Game.h"

Game::Game(sf::RenderWindow* window)
{
	this->window = window;
	isRunning = true;
	toMenu = false;
	grid = new Grid(sf::Vector2f(26, 15));				// ~same ratio as 1280 x 720
	snake = new Player(grid, sf::Vector2f(0, 0));

	// display when the player dies
	displayBoard.setSize(sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2));
	displayBoard.setFillColor(sf::Color(0, 111, 60));
	displayBoard.setPosition(sf::Vector2f((window->getSize().x / 2) - (displayBoard.getSize().x / 2), (window->getSize().y / 2) - (displayBoard.getSize().y / 2)));
	displayBoard.setOutlineColor(sf::Color(38, 75, 150));
	displayBoard.setOutlineThickness(20);
}

Game::~Game()
{
	delete snake;
	delete grid;
}

gameMode Game::run()
{
	// [TIME] resetting the clock for frame-independent speeds
	clock.restart();

	// [GAME-LOOP] main game loop
	while (isRunning)
	{
		handleEvents();										// [GAME] handle SFML events

		updateGameState();									// [GAME] update sprites, logic, etc.

		drawGameState();									// [GAME] draws onto the buffer

		window->display();									// [GAME] updates the frame and copies buffer onto the screen
	}

	if (toMenu) return menu;
	else return score;
}

void Game::handleEvents()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				isRunning = false;
				toMenu = true;
			}

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				snake->changeDir(sf::Vector2f(-1, 0));

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				snake->changeDir(sf::Vector2f(1, 0));

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				snake->changeDir(sf::Vector2f(0, -1));

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				snake->changeDir(sf::Vector2f(0, 1));
		}
	}
}

void Game::updateGameState()
{
	dt = clock.getElapsedTime().asSeconds();			// [TIME] calc delta-time
	if (dt >= 1/snake->getSpeed())
	{
		snake->move();
		clock.restart();
	}
}

void Game::drawGameState()
{
	window->clear(sf::Color(sf::Color(246, 253, 195)));

	for (int x = 0; x < grid->getSize().x; x++)
	{
		for (int y = 0; y < grid->getSize().y; y++)
		{
			grid->getTile()->setPosition(sf::Vector2f(grid->getOffset().x + (x * grid->getTile()->getSize().x), grid->getOffset().y + (y * grid->getTile()->getSize().y)));
			window->draw(*(grid->getTile()));
		}
	}

	grid->getFoodTile()->setPosition(sf::Vector2f(grid->getOffset().x + (grid->getFoodPos().x * grid->getTile()->getSize().x), grid->getOffset().y + (grid->getFoodPos().y * grid->getTile()->getSize().y)));
	window->draw(*(grid->getFoodTile()));

	for (sf::Vector2f body : snake->body)
	{
		snake->getTile()->setPosition(sf::Vector2f(grid->getOffset().x + (body.x * grid->getTile()->getSize().x), grid->getOffset().y + (body.y * grid->getTile()->getSize().y)));
		window->draw(*(snake->getTile()));
	}

	if (!snake->isAlive())
	{
		window->draw(displayBoard);
	}
}
