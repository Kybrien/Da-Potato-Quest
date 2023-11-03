#pragma once
#include "SFML/Graphics.hpp"
#include "Component.h"

class Weapon : public Component {
public:
	Weapon(sf::RenderWindow* window, GameObject* character, std::string fileName, int damage);
	~Weapon() override;
	
	void Attack();

	void Update() override;
	void Render(sf::RenderWindow* _window) override;

private:
	sf::Texture texture;
	sf::Sprite* sprite = nullptr;
	sf::RenderWindow* window = nullptr;
	GameObject* character;
	int damage = 1;
	int count = 0;
};