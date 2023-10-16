#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Menu.h"
#include "Score.h"

int main()
{
	// [SCREEN INIT] setup and open the screen.
	const int WIDTH = 1280, HEIGHT = 720;
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Snake!");
	window.setFramerateLimit(30);

	gameMode currMode = game;

	switch (currMode)
	{
	case menu:
	{
		Menu *mainMenu = new Menu(&window);
		mainMenu->run();
		delete mainMenu;
		break;
	}
	case game:
	{
		Game *mainGame = new Game(&window);
		currMode = mainGame->run();
		delete mainGame;
		break;
	}
	case score:
	{
		Score *playerScore = new Score(&window);
		playerScore->run();
		delete playerScore;
		break;
	}
	default:
		break;
	}


	return 0;
}