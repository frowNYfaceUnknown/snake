#include <string.h>
#include <iostream>											// DEBUG ONLY
#include "Game.h"

Game::Game(sf::RenderWindow* window, sf::Font* font)
{
	this->window = window;
	isRunning = true;
	dt = 0;
	grid = new Grid(sf::Vector2f(26, 15));					// ~same ratio as 1280 x 720
	snake = new Player(grid, sf::Vector2f(0, 0));

	// [GRAPHICS] for visuals
	score = "SCORE:";
	const int OFFSET = 80;

	displayWindow.setSize(sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2));
	displayWindow.setPosition(sf::Vector2f(window->getSize().x / 2 - displayWindow.getSize().x / 2, window->getSize().y / 2 - displayWindow.getSize().y / 2));
	displayWindow.setFillColor(sf::Color(72, 58, 171));
	displayWindow.setOutlineColor(sf::Color(91, 78, 180));
	displayWindow.setOutlineThickness(20);

	scoreText.setFont(*font);
	scoreText.setPosition(sf::Vector2f(window->getSize().x / 2 - scoreText.getGlobalBounds().width / 2, 5));
	scoreText.setFillColor(sf::Color::White);
	scoreText.setCharacterSize(24);
	
	GmOvrText.setFont(*font);
	GmOvrText.setFillColor(sf::Color::White);
	GmOvrText.setCharacterSize(48);
	GmOvrText.setString("Game Over!");
	GmOvrText.setPosition(sf::Vector2f(window->getSize().x / 2 - GmOvrText.getGlobalBounds().width / 2, window->getSize().y / 2 - GmOvrText.getGlobalBounds().height / 2 - OFFSET));
	
	infoText.setFont(*font);
	infoText.setFillColor(sf::Color::White);
	infoText.setCharacterSize(24);
	infoText.setLineSpacing(2);
	infoText.setString("Press [SPACE]\nto play again!");
	infoText.setPosition(sf::Vector2f(window->getSize().x / 2 - infoText.getGlobalBounds().width / 2, window->getSize().y / 2 - infoText.getGlobalBounds().height / 2 + OFFSET));
	// [GRAPHICS] end
}

Game::~Game()
{
	delete snake;
	delete grid;
}

bool Game::run()
{
	clock.restart();										// [TIME] resetting the clock for frame-independent speeds

	// [GAME-LOOP] main game loop
	bool gameOver = false;
	while (isRunning)
	{
		gameOver = handleEvents();							// [GAME] handle SFML events

		updateGameState();									// [GAME] update sprites, logic, etc.

		drawGameState();									// [GAME] draws onto the buffer

		window->display();									// [GAME] updates the frame and copies buffer onto the screen
	}
	// [GAME-LOOP] end

	return gameOver;
}

bool Game::handleEvents()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (!snake->isAlive() && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				isRunning = false;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				isRunning = false;
				return true;
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

	return false;
}

void Game::updateGameState()
{
	dt = clock.getElapsedTime().asSeconds();				// [TIME] calc delta-time
	if (dt >= 1/snake->getSpeed())
	{
		snake->move();
		clock.restart();
	}

	std::string temp = score + std::to_string(snake->getLength() - 1);
	scoreText.setString(temp);
}

void Game::drawGameState()
{
	window->clear(sf::Color(72, 58, 171));
	
	scoreText.setPosition(sf::Vector2f(window->getSize().x / 2 - scoreText.getGlobalBounds().width / 2, 5));
	window->draw(scoreText);

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
		window->draw(displayWindow);
		window->draw(GmOvrText);
		window->draw(infoText);
	}
}
