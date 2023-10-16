#pragma once
#include<SFML/Graphics.hpp>
#include "Grid.h"
#include "Player.h"

enum gameMode
{
	menu,
	game,
	score
};

class Game
{
public:
	Game(sf::RenderWindow* window);
	~Game();
	gameMode run();
	void handleEvents();
	void updateGameState();
	void drawGameState();
private:
	double dt;								// [TIME] Defining the delta-time
	sf::Clock clock;						// [TIME] Defining the clock object
	sf::RenderWindow* window;
	bool isRunning, toMenu;
	Grid* grid;
	Player* snake;

	// variables for when the player dies
	sf::RectangleShape displayBoard;
};