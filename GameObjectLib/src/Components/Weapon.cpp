#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include "Components/Weapon.h"
#include "Components/Sprite.h"
#include "SFML/Graphics.hpp"

Weapon::Weapon(sf::RenderWindow* window, GameObject* character, std::string fileName, int damage)
{
	if (texture.loadFromFile("assets/sprites/" + fileName + ".png")) {
		sprite = new sf::Sprite(texture);
		//sprite->setScale(sf::Vector2f(1 / (texture.getSize().y / 16), 1 / (texture.getSize().y / 16)));
		std::cout << "Weapon " << fileName << " loaded." << std::endl;
	}
	else {
		std::cout << "SA MARCHE PAS" << std::endl;
	}
    this->window = window;
	this->character = character;
	this->damage = damage;
}

Weapon::~Weapon()
{
	
}

void Weapon::Update() 
{
	//owner->SetPosition(character->GetPosition());
}

void Weapon::Render(sf::RenderWindow* _window)
{
	Component::Render(_window);

	const auto ownerPos = GetOwner()->GetPosition();
	sprite->setPosition(ownerPos.x, ownerPos.y);

	_window->draw(*sprite);

	std::cout << texture.getSize().x;
}
