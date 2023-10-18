#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"

int main()
{
	// [SCREEN INIT] setup and open the screen.
	const int WIDTH = 1280, HEIGHT = 720;
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Snake!");
	window.setFramerateLimit(30);
	// [SCREEN INIT] end

	// [FONT & TEXT] load font
	sf::Font font;
	if (!font.loadFromFile("QuinqueFive.ttf"))
	{
		std::cout << "Font File not found." << std::endl;
		return -1;
	}
	// [FONT & TEXT] end

	bool gameOver = false;
	while (!gameOver)
	{
		// [GAME] create, run and destroy main game
		Game *mainGame = new Game(&window, &font);
		gameOver = mainGame->run();
		delete mainGame;
		// [GAME] end
	}

	return 0;
}