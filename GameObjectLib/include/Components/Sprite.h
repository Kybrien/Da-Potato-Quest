#pragma once

#include <SFML/Graphics.hpp>
#include "Component.h"

class Sprite : public Component
{
public:
	Sprite(std::string texture);
	~Sprite() override;

	void Render(sf::RenderWindow* _window) override;

private:
	sf::Texture texture;
	sf::Sprite* sprite = nullptr;
};
