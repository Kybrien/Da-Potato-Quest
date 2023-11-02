#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include "Components/Weapon.h"
#include "Components/Sprite.h"
#include "SFML/Graphics.hpp"

Weapon::Weapon(sf::RenderWindow* window, GameObject* character, int damage)
{
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

}
