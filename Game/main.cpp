#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>

#include "TileMap.h"

#include "GameObject.h"
#include "Components/Sprite.h"
#include "Components/MusicComponent.h"
#include "Scene.h"
#include "Menu.h"


void ProcessInput(GameObject* player, float dt, Scene scene)
{
	auto playerSprite = player->getComponent<Sprite>();
	playerSprite->setOldPosition(player->GetPosition());

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		player->SetPosition(player->GetPosition() + Maths::Vector2f(1, 0) * dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		player->SetPosition(player->GetPosition() + Maths::Vector2f(-1, 0) * dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
		player->SetPosition(player->GetPosition() + Maths::Vector2f(0, -1) * dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		player->SetPosition(player->GetPosition() + Maths::Vector2f(0, 1) * dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		auto window = new sf::RenderWindow(sf::VideoMode(800, 600), "DA POOTATO QUEST", sf::Style::Default);
		window->setFramerateLimit(60);
		Menu menu(window);
		menu.MainMenu();
	}
}

void HandleCamera(sf::RenderWindow* window, sf::View camera, GameObject* player, TileMap map) {
	sf::Vector2f playerPosition = sf::Vector2f(player->GetPosition().x, player->GetPosition().y);

	sf::Vector2u windowSize(window->getSize().x, window->getSize().y);

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

bool isGamePaused = false;
bool isMenuActive = false;

int main()
{
	Scene scene;

	GameObject* player = scene.CreateDummyGameObject("Player", 200.f, "potato.png", 0.015f);

	scene.setPlayer(player);

	//GameObject* enemy = scene.CreateDummyGameObject("Enemy", 400.f, "potato.png", 0.02f);

	auto window = new sf::RenderWindow(sf::VideoMode(800, 600), "DA POOTATO QUEST", sf::Style::Default);
	//window->setVerticalSyncEnabled(true);
	window->setFramerateLimit(60);

	//MusicComponent music(nullptr);
	//music.LoadMusic("music.ogg");
	//music.Play(true);

	Menu menu(window);
	menu.MainMenu();

	TileMap map;
	map.loadmap("Lvl01", scene);

	scene.setCamera(CreateCamera(window, 5));

	sf::Clock clock;
	sf::Time time;

	float dt = 0;
	const int speed = 50;

	sf::View camera = scene.getCamera(); // Obtenir la vue de la caméra depuis la classe Scene

	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					// Mettre en pause ou reprendre le jeu
					isGamePaused = !isGamePaused;
					isMenuActive = isGamePaused; // Activer le menu si le jeu est en pause
				}
			}
		}

		if (!isGamePaused)
		{
			// Mettre à jour le jeu uniquement si le jeu n'est pas en pause
			time = clock.restart();
			dt = time.asSeconds();
			ProcessInput(player, dt * speed, scene);
			scene.Update();
			HandleCamera(window, camera, player, map);
		}

		window->clear(sf::Color::Black);
		window->draw(map);
		scene.Render(window);

		// Afficher le menu pause si le jeu est en pause
		if (isMenuActive)
		{
			// Dessiner votre menu pause ici
			// ...
		}

		window->display();
	}


	return 0;
}
