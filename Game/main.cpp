#include <iostream>

#include <SFML/Graphics.hpp>

#include "TileMap.h"

#include "GameObject.h"
#include "Scene.h"
#include "Menu.h"

void ProcessInput(GameObject* player, float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		player->SetPosition(player->GetPosition() + Maths::Vector2f(1, 0) * dt * 2);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		player->SetPosition(player->GetPosition() + Maths::Vector2f(-1, 0) * dt * 2);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		player->SetPosition(player->GetPosition() + Maths::Vector2f(0, -1) * dt * 2);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		player->SetPosition(player->GetPosition() + Maths::Vector2f(0, 1) * dt * 2);
}

int main()
{
	Scene scene;

	GameObject* player = scene.CreateDummyGameObject("Player", 200.f, "potato.png");

	GameObject* enemy = scene.CreateDummyGameObject("Enemy", 400.f, "potato.png");

	auto window = new sf::RenderWindow(sf::VideoMode(640, 480), "SFML Engine");

	//Menu menu(window);
	
	const int level[] =
	{
		0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
		0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
		0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
		0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
		2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
		0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
	};

	TileMap map;
	//if (!map.load("assets/tilesets/Hills.png", sf::Vector2u(16, 16), level, 16, 8))
	//	return -1;

	map.loadmap("PotatoV1");

	sf::Clock clock;
	sf::Time time;

	float dt = 0;
	const int speed = 100;

	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}

		time = clock.restart();
		dt = time.asSeconds();

		ProcessInput(player, dt * speed);

		scene.Update();
		window->clear(sf::Color::Black);
		window->draw(map);
		scene.Render(window);
		window->display();
	}


	return 0;
}
