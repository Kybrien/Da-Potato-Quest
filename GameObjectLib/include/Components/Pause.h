#pragma once
#include "Component.h"
#include "SFML/Graphics.hpp"

class Pause : public Component
{
public:
	Pause(sf::RenderWindow* _window);
	~Pause();

	Scene InitPause();

	void CreatePauseMenu();

	void Close();

	std::vector<GameObject*> GetButtons() { return buttons; }

	void RenderPauseMenu();
	//void MoveUp();
	//void MoveDown();

private:
	sf::RenderWindow* menuWindow = nullptr;
	Scene* menu = nullptr;
	sf::Texture* background = nullptr;
	std::vector<GameObject*> buttons;
	bool open = true;
};

