#pragma once
#include "GameObject.h"
#include "Maths/Vector2.h"
#include "SFML/Graphics.hpp"

class Sprite : public Component {
public:
	sf::Sprite sprite;
	Sprite(GameObject* owner, std::string texture) : Component(owner) {}
	void Move(Vector2<double> direction);

	virtual void update() override;

protected:
	//sf::Sprite sprite;
	int speed = 1;
};