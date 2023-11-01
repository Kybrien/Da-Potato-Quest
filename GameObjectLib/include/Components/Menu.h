#pragma once
#include "Component.h"
#include "SFML/Graphics.hpp"
#define MAX_NUMBER_OF_ITEMS 3

class Menu : public Component
{
public:
	Menu(sf::RenderWindow* _window);
	~Menu();

	Scene CreateMenu();

	void RenderMainMenu();

	void Close();

	void RenderMenu();
	void MoveUp();
	void MoveDown();
	void IsClicked(const sf::Vector2f& mousePos);

private:
	sf::RenderWindow* menuWindow = nullptr;
	Scene* menu = nullptr;
	sf::Texture* background = nullptr;
	bool open = true;
};

