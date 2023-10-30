#pragma once

#include <SFML/Graphics.hpp>
#include "Component.h"

class Button : public Component
{
public:
	Button(sf::RenderWindow* _window, Maths::Vector2f size, std::string text);
	~Button() override;

	void Render(sf::RenderWindow* _window) override;
	bool IsClicked(const sf::Vector2f& mousePos) const {
		sf::FloatRect buttonBounds = shape->getGlobalBounds();
		return buttonBounds.contains(mousePos);
	}

private:
	sf::Color color = sf::Color::Blue;
	sf::Text* text = nullptr;
	sf::RectangleShape* shape = nullptr;
};
