#include <memory>
#include "Game.h"

#include "Components/SaveComponent.h"
#include "Components/Menu.h"
#include "Components/Sprite.h"
#include "Components/Button.h"

void Game::ProcessInput(GameObject* player, float dt, Scene scene)
{
	auto playerSprite = player->getComponent<Sprite>();
	playerSprite->setOldPosition(player->GetPosition());

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		player->SetPosition(player->GetPosition() + Maths::Vector2f(1, 0) * dt);
		playerSprite->setAnimation(2);
		playerSprite->count++;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		player->SetPosition(player->GetPosition() + Maths::Vector2f(-1, 0) * dt);
		playerSprite->setAnimation(3);
		playerSprite->count++;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
		player->SetPosition(player->GetPosition() + Maths::Vector2f(0, -1) * dt);
		playerSprite->setAnimation(1);
		playerSprite->count++;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		player->SetPosition(player->GetPosition() + Maths::Vector2f(0, 1) * dt);
		playerSprite->setAnimation(0);
		playerSprite->count++;
	}
}

void Game::HandleCamera(sf::View camera, GameObject* player, TileMap map) {
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

sf::View Game::CreateCamera(float zoom) {
	sf::View camera;
	camera.setSize(window->getSize().x / zoom, window->getSize().y / zoom);
	camera.setCenter(0, 0);
	window->setView(camera);
	return camera;
}

void Game::Init() {
	window = new sf::RenderWindow(sf::VideoMode(800, 600), "DA POOTATO QUEST", sf::Style::Default);
	//window->setVerticalSyncEnabled(true);
	window->setFramerateLimit(60);
	window->setKeyRepeatEnabled(false);

	//sf::Texture perso;
	//sf::Sprite sprite_perso;
	//enum Dir { Up, Down, Right, Left };
	//sf::Vector2i animation(1, Down);
	//animation.x++;
	//if (animation.x * 32 >= perso.getSize().x)

	player = scene.CreateDummyGameObject("Player", 200.f, "sprite_potato.png", 0.5f);
	scene.setPlayer(player);
}

void Game::Run() {
	Menu menu(window);
	menu.Init();
	menu.CreateMainMenu();

	std::cout << "GAME STARTED" << std::endl;

	//-----------------------------------------------------------------------------------------------------------//
	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("assets/images/background.png")) {
		// Gérer l'erreur si le chargement échoue
	}

	// Créer le rectangle de fond (background) avec la texture chargée
	sf::RectangleShape background(sf::Vector2f(window->getSize().x, window->getSize().y));
	background.setTexture(&backgroundTexture); // Appliquer la texture à la forme
	//-----------------------------------------------------------------------------------------------------------//

	//MusicComponent music(nullptr);
	//music.LoadMusic("music.ogg");
	//music.Play(true);

	TileMap map;
	map.loadmap("Lvl01", scene);

	SaveComponent save(nullptr);
	save.LoadSave(player);

	sf::Clock clock;
	sf::Time time;

	float dt = 0;
	const int speed = 50;

	std::cout << gameState;

	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();

			if (event.type == (sf::Event::KeyPressed)) {
				if (event.key.code == sf::Keyboard::Escape) {
					std::cout << "escape pressed";
					gameState == PLAYING ? gameState = PAUSE : gameState = PLAYING;
				}
			}

			if (event.type == sf::Event::MouseButtonPressed) {
				if (gameState == MAIN_MENU) {
					sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

					// Vérifier si le bouton 1 est cliqué
					menu.GetButtons();
					if (menu.GetButtons()[0]->getComponent<Button>()->IsClicked(mousePos)) {
						gameState = PLAYING;
					}

					// Vérifier si le bouton 2 est cliqué
					else if (menu.GetButtons()[1]->getComponent<Button>()->IsClicked(mousePos)) {
						// Faites quelque chose avec le bouton 2
					}

					// Vérifier si le bouton 3 est cliqué
					else if (menu.GetButtons()[2]->getComponent<Button>()->IsClicked(mousePos)) {
						window->close();
						//quitte le programme
					}
				}
			}
		}

		time = clock.restart();
		dt = time.asSeconds();

		if (gameState == MAIN_MENU) {
			window->clear();
			window->draw(background);

			menu.RenderMenu();
			window->display();
		}
		if (gameState == PLAYING) {
			ProcessInput(player, dt * speed, scene);

			scene.setCamera(CreateCamera(5));

			scene.Update();
			HandleCamera(scene.getGamera(), player, map);
			window->clear(sf::Color::Black);
			window->draw(map);
			scene.Render(window);
			window->display();
		}
		if (gameState == PAUSE) {

		}
	}
	save.Save(player);
}