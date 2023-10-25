#include <SFML/Graphics.hpp>

#include "GameObject.h"
#include "Scene.h"
#include <iostream>

int main()
{
	Scene scene;

	GameObject* player = scene.CreateDummyGameObject("Player", 200.f, "potato.png");

	GameObject* enemy = scene.CreateDummyGameObject("Enemy", 400.f, "potato.png");	

	MusicComponent musicComponent(nullptr);
	musicComponent.LoadMusic("music.ogg");
	musicComponent.Play();

	sf::Texture texture;
	if (!texture.loadFromFile("resources/potato.png"))
		return EXIT_FAILURE;
	sf::Sprite sprite(texture);

	auto window = new sf::RenderWindow(sf::VideoMode(300, 300), "SFML Engine");

	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
			if (event.type == sf::Event::KeyPressed)
				if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D)
					player->SetPosition(player->GetPosition() + Maths::Vector2f::Right);
				if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Q)
					player->SetPosition(player->GetPosition() + Maths::Vector2f::Left);
				if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Z)
					player->SetPosition(player->GetPosition() + Maths::Vector2f::Up);
				if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)
					player->SetPosition(player->GetPosition() + Maths::Vector2f::Down);
		}

		scene.Update();
		window->clear(sf::Color::Black);
		scene.Render(window);
		window->display();
	}

	return 0;
}
