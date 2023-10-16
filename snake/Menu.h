#pragma once
#include <SFML/Graphics.hpp>

class Menu
{
public:
	Menu(sf::RenderWindow* window);
	~Menu();
	void run();
};