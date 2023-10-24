#include "Objects/Sprite.h"

Sprite::Sprite(GameObject* owner, std::string texture) : Component(owner) {
	sf::Texture newTexture;
	if (newTexture.loadFromFile(texture))
		this->sprite = sf::Sprite(newTexture);
}

void Sprite::Move(Vector2<double> direction) {
	this->owner->setPosition(owner->getPosition().x + (direction * this->speed).x, owner->getPosition().y + (direction * this->speed).y);
}

void Sprite::update() {
	std::cout << "updating le truc z";
}