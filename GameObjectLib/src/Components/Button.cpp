#include "Components/Button.h"
#include "SFML/Graphics/Shape.hpp"

Button::Button(std::string text)
{
	shape = new sf::RectangleShape();
	this->text = new sf::Text;
	sf::Font* font = new sf::Font;
	if (font->loadFromFile("assets/fonts/arial.ttf")) {
		this->text = new sf::Text;
		this->text->setString(text);
		this->text->setFont(*font);
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
	shape->setSize(sf::Vector2f(300.f, 120.f));
	shape->setFillColor(color);
	text->setPosition(position.x, position.y);
	text->setCharacterSize(24);
	text->setFillColor(sf::Color::Red);

	_window->draw(*shape);
	_window->draw(*text);
}

