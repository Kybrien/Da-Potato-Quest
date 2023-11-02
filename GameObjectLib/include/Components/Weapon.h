#pragma once
#include "SFML/Graphics.hpp"
#include "Component.h"

class Weapon : public Component {
public:
	Weapon(sf::RenderWindow* window, GameObject* character, int damage);
	~Weapon() override;

	void Update() override;
	void Render(sf::RenderWindow* _window) override;

private:
	sf::RenderWindow* window = nullptr;
	GameObject* character;
	int damage = 1;
};