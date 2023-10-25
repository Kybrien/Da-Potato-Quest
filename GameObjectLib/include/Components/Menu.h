#pragma once
#include "Component.h"
#include "SFML/Graphics.hpp"
#define MAX_NUMBER_OF_ITEMS 3

class Menu : public Component
{
public:
	Menu(sf::RenderWindow* _window);
	~Menu();

	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();

private:
	int selectedItemIndex;
	//sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
};

