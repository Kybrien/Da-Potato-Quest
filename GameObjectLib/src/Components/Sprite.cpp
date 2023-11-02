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

void Sprite::moveBack(int direction) {
	if (GetOwner()) {
		switch (direction) {
		case 0:
			GetOwner()->SetPosition(Maths::Vector2f(oldPosition.x, GetOwner()->GetPosition().y));
			break;
		case 1:
			GetOwner()->SetPosition(Maths::Vector2f(GetOwner()->GetPosition().x, oldPosition.y));
			break;
		default:
			break;
		}
	}
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
	if (count > anim_speed) {
		Animation.x++;
		if (Animation.x * 32 >= texture.getSize().x) {
			Animation.x = 0;
		}
		sprite->setTextureRect(sf::IntRect(Animation.x * 32, Animation.y * 32, 32, 32));
		count = 0;
	}

}

void Sprite::Render(sf::RenderWindow* _window)
{
	Component::Render(_window);

	const auto ownerPos = GetOwner()->GetPosition();
	sprite->setPosition(ownerPos.x, ownerPos.y);

	_window->draw(*sprite);
}
