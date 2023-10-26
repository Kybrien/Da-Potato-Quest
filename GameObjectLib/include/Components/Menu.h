#pragma once
#include "Component.h"
#include "SFML/Graphics.hpp"
#define MAX_NUMBER_OF_ITEMS 3

class Menu : public Component
{
public:
	Menu(sf::RenderWindow* _window);
	~Menu();

	Scene MainMenu();

	void Close();

	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	void IsClicked(const sf::Vector2f& mousePos);

private:
	Scene* menu = nullptr;
	sf::RenderWindow* menuWindow;
	bool open = true;
};

