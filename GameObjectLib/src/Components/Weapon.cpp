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
		sprite->setScale(0.5, 0.5);
		sprite->setTextureRect(sf::IntRect(0 * sprite->getTexture()->getSize().y, 0, sprite->getTexture()->getSize().y, sprite->getTexture()->getSize().y));
		std::cout << "Weapon " << fileName << " loaded." << std::endl;
	}
    this->window = window;
	this->character = character;
	this->damage = damage;
}

Weapon::~Weapon()
{
	
}

void Weapon::Attack()
{
	count = 0;
}

void Weapon::Update() 
{
	if (count / 2 < sprite->getTexture()->getSize().x / sprite->getTexture()->getSize().y) {
		++count;
		sprite->setTextureRect(sf::IntRect((count / 2) * sprite->getTexture()->getSize().y, 0, sprite->getTexture()->getSize().y, sprite->getTexture()->getSize().y));
	}
	//owner->SetPosition(character->GetPosition());
}

void Weapon::Render(sf::RenderWindow* _window)
{
	Component::Render(_window);

	const auto ownerPos = GetOwner()->GetPosition();
	sprite->setPosition(ownerPos.x, ownerPos.y);

	_window->draw(*sprite);
}
