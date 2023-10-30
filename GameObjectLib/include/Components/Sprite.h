#pragma once

#include <SFML/Graphics.hpp>
#include "Component.h"

class Sprite : public Component
{
public:
	Sprite(std::string texture, float scale);
	~Sprite() override;

	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	void moveBack(int direction);

	void setOldPosition(Maths::Vector2f position);
	Maths::Vector2f getOldPosition();
	float getOldXPosition();
	float getOldYPosition();

	void Update() override;
	void Render(sf::RenderWindow* _window) override;

private:
	sf::Texture texture;
	sf::Sprite* sprite = nullptr;
	Maths::Vector2f oldPosition;
};
