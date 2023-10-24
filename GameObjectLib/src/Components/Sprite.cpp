#include "Components/Sprite.h"
#include "SFML/Graphics.hpp"

Sprite::Sprite(std::string newTexture)
{
	if (texture.loadFromFile("resources/" + newTexture))
		sprite = new sf::Sprite(texture);
}

Sprite::~Sprite()
{
	delete sprite;
	sprite = nullptr;
}

void Sprite::Render(sf::RenderWindow* _window)
{
	Component::Render(_window);

	const auto position = GetOwner()->GetPosition();
	sprite->setPosition(position.x, position.y);

	_window->draw(*sprite);
}
