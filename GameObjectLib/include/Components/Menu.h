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
	void CreatePauseMenu();
	void CreateOptionMenu();

	void MainMenu();
	void PauseMenu();
	void OptionMenu();

	void Close();
	sf::RectangleShape* GetBackground() { return background; }
	
	std::vector<GameObject*> GetButtons() { return buttons; }

	void RenderMenu();
	//void MoveUp();
	//void MoveDown();

private:
	sf::RenderWindow* menuWindow = nullptr;
	Scene* menu = nullptr;
	std::vector<sf::Texture*> backgroundImages;
	sf::RectangleShape* background = nullptr;
	std::vector<GameObject*> buttons;
	bool open = true;
};

