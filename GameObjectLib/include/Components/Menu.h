#pragma once
#include "Component.h"
#include "SFML/Graphics.hpp"
#define MAX_NUMBER_OF_ITEMS 3

class Menu : public Component
{
public:
	Menu(sf::RenderWindow* _window);
	~Menu();

	Scene Init();

	void CreateMainMenu();

	void Close();
	
	std::vector<GameObject*> GetButtons() { return buttons; }

	void RenderMenu();
	//void MoveUp();
	//void MoveDown();

private:
	sf::RenderWindow* menuWindow = nullptr;
	Scene* menu = nullptr;
	sf::Texture* background = nullptr;
	std::vector<GameObject*> buttons;
	bool open = true;
};

