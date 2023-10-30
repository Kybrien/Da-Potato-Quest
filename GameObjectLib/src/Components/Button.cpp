#include <iostream>
#include "Components/Button.h"
#include "SFML/Graphics/Shape.hpp"

Button::Button(sf::RenderWindow* _window, Maths::Vector2f size, std::string text)
{
	shape = new sf::RectangleShape();
	shape->setSize(sf::Vector2f(size.x * _window->getSize().x, size.y * _window->getSize().y));
	shape->setFillColor(sf::Color::Transparent);
	this->text = new sf::Text;
	sf::Font* font = new sf::Font;
	if (font->loadFromFile("assets/fonts/alagard.ttf")) {
		this->text = new sf::Text;
		this->text->setString(text);
		this->text->setFont(*font);
		this->text->setCharacterSize(24);
		this->text->setFillColor(sf::Color::Black);
	}
}

Button::~Button()
{
	delete shape;
	shape = nullptr;
}

void Button::Render(sf::RenderWindow* _window)
{
	Component::Render(_window);

	const auto position = GetOwner()->GetPosition();
	shape->setPosition(position.x, position.y);
	float textX = position.x + (shape->getSize().x - text->getLocalBounds().width) / 2;
	float textY = position.y + (shape->getSize().y - text->getLocalBounds().height) / 2 - 5;
	text->setPosition(textX, textY);

	_window->draw(*shape);
	_window->draw(*text);
}

