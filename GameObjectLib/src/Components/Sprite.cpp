#include <iostream>
#include "Components/Sprite.h"
#include "SFML/Graphics.hpp"

Sprite::Sprite(std::string newTexture, float scale)
{
	if (texture.loadFromFile("assets/sprites/" + newTexture)) {
		sprite = new sf::Sprite(texture);
		sprite->setScale(scale, scale);
	}
}

Sprite::~Sprite()
{
	delete sprite;
	sprite = nullptr;
}

void Sprite::moveLeft() {

}

void Sprite::setOldPosition(Maths::Vector2f position) {
	oldPosition = position;
}

Maths::Vector2f Sprite::getOldPosition() {
	return oldPosition;
}

float Sprite::getOldXPosition() {
	return oldPosition.x;
}

float Sprite::getOldYPosition() {
	return oldPosition.y;
}

void Sprite::Update() {

}

void Sprite::Render(sf::RenderWindow* _window)
{
	Component::Render(_window);

	const auto ownerPos = GetOwner()->GetPosition();
	sprite->setPosition(ownerPos.x, ownerPos.y);

	_window->draw(*sprite);
}
