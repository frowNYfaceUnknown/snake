#pragma once
#include<SFML/Graphics.hpp>
#include "Grid.h"
#include "Player.h"

class Game
{
public:
	Game(sf::RenderWindow* window, sf::Font* font);
	~Game();
	bool run();
	bool handleEvents();
	void updateGameState();
	void drawGameState();
private:
	double dt;												// [TIME] Defining the delta-time
	sf::Clock clock;										// [TIME] Defining the clock object
	sf::RenderWindow* window;
	bool isRunning;
	Grid* grid;
	Player* snake;

	// [GRAPHICS] for visuals
	sf::RectangleShape displayWindow;
	sf::Text scoreText;
	std::string score;
	sf::Text GmOvrText;
	sf::Text infoText;
	// [GRAPHICS] end
};