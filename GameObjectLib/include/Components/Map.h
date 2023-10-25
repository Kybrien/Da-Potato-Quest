#pragma once

#include <SFML/Graphics.hpp>
#include "Component.h"

class Map : public Component
{
public:
	Map(std::string map);
	~Map() override;

	void Render(sf::RenderWindow* _window) override;

private:
	std::vector<int> layers;
	sf::Sprite* sprite = nullptr;
};
