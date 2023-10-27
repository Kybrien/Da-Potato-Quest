#include <iostream>

#include <SFML/Graphics.hpp>

#include "TileMap.h"

#include "GameObject.h"
#include "Components/MusicComponent.h"
#include "Scene.h"
#include "Menu.h"

void ProcessInput(GameObject* player, float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		player->SetPosition(player->GetPosition() + Maths::Vector2f(1, 0) * dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		player->SetPosition(player->GetPosition() + Maths::Vector2f(-1, 0) * dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		player->SetPosition(player->GetPosition() + Maths::Vector2f(0, -1) * dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		player->SetPosition(player->GetPosition() + Maths::Vector2f(0, 1) * dt);
}

void HandleCamera(sf::RenderWindow* window, sf::View camera, GameObject* player, TileMap map) {
	sf::Vector2f playerPosition = sf::Vector2f(player->GetPosition().x, player->GetPosition().y);

	sf::Vector2f windowSize(window->getSize().x, window->getSize().y);

	sf::Vector2f cameraSize = camera.getSize();

	float halfCameraWidth = cameraSize.x / 2.0f;
	float halfCameraHeight = cameraSize.y / 2.0f;

	if (playerPosition.x - halfCameraWidth < 0) {
		playerPosition.x = halfCameraWidth;
	}
	if (playerPosition.x + halfCameraWidth > map.getWidth()) {
		playerPosition.x = map.getWidth() - halfCameraWidth;
	}
	if (playerPosition.y - halfCameraHeight < 0) {
		playerPosition.y = halfCameraHeight;
	}
	if (playerPosition.y + halfCameraHeight > map.getHeight()) {
		playerPosition.y = map.getHeight() - halfCameraHeight;
	}

	camera.setCenter(playerPosition);

	window->setView(camera);
}

sf::View CreateCamera(sf::RenderWindow* window, float zoom) {
	sf::View camera;
	camera.setSize(window->getSize().x / zoom, window->getSize().y / zoom);
	camera.setCenter(0, 0);
	window->setView(camera);
	return camera;
}

int main()
{
	Scene scene;

	GameObject* player = scene.CreateDummyGameObject("Player", 200.f, "potato.png");

	GameObject* enemy = scene.CreateDummyGameObject("Enemy", 400.f, "potato.png");

	auto window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "SFML Engine");

	MusicComponent music(nullptr);
	music.LoadMusic("music.ogg");
	music.Play(true);

	Menu menu(window);
	menu.MainMenu();

	TileMap map;
	map.loadmap("test2");

	scene.setCamera(CreateCamera(window, 5));

	sf::Clock clock;
	sf::Time time;

	float dt = 0;
	const int speed = 60;

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
		HandleCamera(window, scene.getGamera(), player, map);
		window->clear(sf::Color::Black);
		window->draw(map);
		scene.Render(window);
		window->display();
	}


	return 0;
}
