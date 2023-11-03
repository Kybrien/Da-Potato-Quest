#include <memory>
#include "Game.h"

#include "Components/SaveComponent.h"
#include "Components/MusicComponent.h"
#include "Components/Menu.h"
#include "Components/Sprite.h"
#include "Components/Button.h"
#include "Components/HealthBar.h"
#include "Components/Achievement.h"
#include "Components/MusicComponent.h"
#include "Components/Weapon.h"
#include <random>

void Game::ProcessInput(GameObject* player, float dt, Scene scene)
{
	auto playerSprite = player->getComponent<Sprite>();
	playerSprite->setOldPosition(player->GetPosition());

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		player->SetPosition(player->GetPosition() + Maths::Vector2f(1, 0) * dt);
		playerSprite->setAnimation(2);
		playerSprite->incrementCount();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		player->SetPosition(player->GetPosition() + Maths::Vector2f(-1, 0) * dt);
		playerSprite->setAnimation(3);
		playerSprite->incrementCount();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
		player->SetPosition(player->GetPosition() + Maths::Vector2f(0, -1) * dt);
		playerSprite->setAnimation(1);
		playerSprite->incrementCount();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		player->SetPosition(player->GetPosition() + Maths::Vector2f(0, 1) * dt);
		playerSprite->setAnimation(0);
		playerSprite->incrementCount();
	}
}

void Game::FollowPlayer(GameObject* enemy, float dt, Scene scene)
{
	auto EnemySprite = enemy->getComponent<Sprite>();
	EnemySprite->setOldPosition(enemy->GetPosition());

	int distX = player->GetPosition().GetX() - enemy->GetPosition().GetX();
	int distY = player->GetPosition().GetY() - enemy->GetPosition().GetY();

	float distance = enemy->GetPosition().Distance(player->GetPosition());

	//if (distance > 75) {
	//	return;
	//}

	if (distX < 0) {
		enemy->SetPosition(enemy->GetPosition() + Maths::Vector2f(-10, 0) * dt);
		EnemySprite->setAnimation(3);
		EnemySprite->count++;
	}
	else if (distX > 0) {
		enemy->SetPosition(enemy->GetPosition() + Maths::Vector2f(+10, 0) * dt);
		EnemySprite->setAnimation(2);
		EnemySprite->count++;
	}
	if (distY < 0) {
		enemy->SetPosition(enemy->GetPosition() + Maths::Vector2f(0, -10) * dt);
		EnemySprite->setAnimation(1);
		EnemySprite->count++;
	}
	else if (distY > 0) {
		enemy->SetPosition(enemy->GetPosition() + Maths::Vector2f(0, +10) * dt);
		EnemySprite->setAnimation(0);
		EnemySprite->count++;
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

	player = scene.CreateDummyGameObject("Player", 200.f, "potato", 3, 0.5f);
	weapon = scene.CreateWeaponGameObject(window, "Weapon", player, 1);

	HealthBar* hb = new HealthBar(player);
	GameObject* healthBar = scene.CreateGameObject("healthBar");
	healthBar->AddComponent(hb);
	this->healthbar = healthBar;

	Achievement* ach = new Achievement(player , "You Killed 3 Ennemies");
	GameObject* achievement = scene.CreateGameObject("achievement");
	achievement->AddComponent(ach);
	this->achievement = achievement;

	MusicComponent* slashSound = new MusicComponent(nullptr);
	slashSound->LoadSound("slash.ogg");
	sounds.push_back(slashSound);

	MusicComponent* deathSound = new MusicComponent(nullptr);
	deathSound->LoadSound("death.ogg");
	sounds.push_back(deathSound);

	GameObject* teleporter = new GameObject;
	SquareCollider* tpCollider = new SquareCollider;
	teleporter->SetPosition(Maths::Vector2f(352.0f, 1344.0f));
	teleporter->AddComponent(tpCollider);
	scene.addTeleporter(teleporter);

	scene.setPlayer(player);
}

void Game::Run() {
	Menu menu(window);
	menu.Init();
	menu.CreateMainMenu();
	menu.CreatePauseMenu();
	menu.CreateOptionMenu();

	std::cout << "GAME STARTED" << std::endl;
	SaveComponent save(nullptr);
	MusicComponent* music = new MusicComponent(nullptr);
	music->LoadMusic("music.ogg");
	save.LoadSave(player, music);
	music->Play(true);
	TileMap map;
	map.loadmap("Lvl01", scene);

	sf::Clock clock;
	bool achievementVisible = false;
	sf::Clock AchievementClock;
	sf::Clock SpawnClock;
	sf::Time time;

	float dt = 0;
	const int speed = 50;

	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();

			if (event.type == (sf::Event::KeyPressed)) {
				if (event.key.code == sf::Keyboard::Escape) {
					if (gameState == PLAYING) {
						gameState = PAUSE;
						menu.PauseMenu();
					}
					else if (gameState == PAUSE) {
						gameState = PLAYING;
						menu.Close();
					}
				}
			}

			if (event.type == sf::Event::MouseButtonPressed) {
				sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
				if (gameState == MAIN_MENU) {
					// Vérifier si le bouton 1 est cliqué
					if (menu.GetButtons()[0]->getComponent<Button>()->IsClicked(mousePos)) {
						gameState = PLAYING;
						menu.Close();
					}

					// Vérifier si le bouton 2 est cliqué
					else if (menu.GetButtons()[1]->getComponent<Button>()->IsClicked(mousePos)) {
						gameState = OPTION;
						menu.OptionMenu();
					}

					// Vérifier si le bouton 3 est cliqué
					else if (menu.GetButtons()[2]->getComponent<Button>()->IsClicked(mousePos)) {
						window->close();
						//quitte le programme
					}
				}
				if (gameState == PLAYING) {
					Sprite* playerSprite = player->getComponent<Sprite>();
					Maths::Vector2f mouseWorldPos = Maths::Vector2f(player->GetPosition().x - 8 + mousePos.x, player->GetPosition().y - 8 + mousePos.y);
					float distance = player->GetPosition().Distance(mouseWorldPos);
					if (distance <= 25 && playerSprite->getAttacking() == false) {
						playerSprite->Attack();
						weapon->getComponent<Weapon>()->Attack();
						weapon->SetPosition(Maths::Vector2f(mouseWorldPos.x + 4, mouseWorldPos.y + 4));
						sounds[0]->Play(false);
						for (int i = 0; i < enemies.size(); i++) {
							GameObject* currEnemy = enemies[i];
							if (SquareCollider::IsColliding(*currEnemy->getComponent<SquareCollider>(), *weapon->getComponent<SquareCollider>())) {
								currEnemy->getComponent<Sprite>()->setCurrentHealth(currEnemy->getComponent<Sprite>()->getCurrentHealth() - 1);
								if (currEnemy->getComponent<Sprite>()->getCurrentHealth() == 0) {
									player->IncrementKill();
									if (player->GetKill() == 3) {
										achievementVisible = true;
										AchievementClock.restart();
									}
									sounds[1]->Play(false);
									currEnemy->getComponent<Sprite>()->Kill();
									enemies[i] = nullptr;
								}
							}
						}

						enemies.erase(std::remove(enemies.begin(), enemies.end(), nullptr), enemies.end());
					}
				}
				if (gameState == PAUSE) {
					if (menu.GetButtons()[3]->getComponent<Button>()->IsClicked(mousePos)) {
						gameState = PLAYING;
						menu.Close();
					}
					if (menu.GetButtons()[4]->getComponent<Button>()->IsClicked(mousePos)) {
						gameState = MAIN_MENU;
						menu.MainMenu();
					}
				}
				if (gameState == OPTION) {
					if (menu.GetButtons()[5]->getComponent<Button>()->IsClicked(mousePos)) {
						music->VolumePlus();
					}
					menu.GetButtons()[6]->getComponent<Button>()->setText(std::to_string(music->GetVolume()));
					if (menu.GetButtons()[7]->getComponent<Button>()->IsClicked(mousePos)) {
						music->VolumeMoins();
					}
					if (menu.GetButtons()[8]->getComponent<Button>()->IsClicked(mousePos)) {
						save.DelSave();
						//Il faut reset le jeu
					}
					if (menu.GetButtons()[9]->getComponent<Button>()->IsClicked(mousePos)) {
						gameState = MAIN_MENU;
						menu.MainMenu();
					}
				}
			}
		}

		time = clock.restart();
		dt = time.asSeconds();

		if (gameState == MAIN_MENU) {
			window->clear();

			menu.GetBackground()->setPosition(0, 0);
			window->draw(*menu.GetBackground());

			menu.RenderMenu();
			window->display();
		}
		if (gameState == PLAYING) {
			// Code pas rangé par manque de temps
			ProcessInput(player, dt * speed, scene);
			for (int i = 0; i < enemies.size(); i++) {
				FollowPlayer(enemies[i], dt, scene);
			}

			if (SquareCollider::IsColliding(*player->getComponent<SquareCollider>(), *scene.getTeleporters()[0]->getComponent<SquareCollider>())) {
				scene.clearCollider();
				map.loadmap("Lvl02", scene);
				player->SetPosition(Maths::Vector2f(112.0f, 64.0f));
			}
			//


			scene.setCamera(CreateCamera(5));

			if (SpawnClock.getElapsedTime().asSeconds() > 5.0f) {
				std::cout << "dummies Spawned" << std::endl;
				for (int i = 0; i != 5; i++) {
					enemies.push_back(scene.CreateDummyGameObject("Enemy" + std::to_string(enemies.size()), 200.f, "enemy_potato", 3, 0.5f));
					std::random_device rd;
					std::mt19937 gen(rd());
					std::uniform_real_distribution<float> dis(0, 16*100);
					float x = dis(gen);
					float y = dis(gen);
					Maths::Vector2<float> SpawnPoint(x, y);
					enemies[enemies.size() - 1]->SetPosition(SpawnPoint);

				}
				SpawnClock.restart();
			}

			scene.Update();
			HandleCamera(scene.getCamera(), player, map);
			window->clear(sf::Color::Black);
			window->draw(map);
			scene.Render(window);
			healthbar->getComponent<HealthBar>()->RenderGui(window);
			if (achievementVisible)
			{
				achievement->getComponent<Achievement>()->RenderGui(window);
				if (AchievementClock.getElapsedTime().asSeconds() > 3.0f)
					achievementVisible = false;
			}
			window->setView(scene.getCamera());
			window->display();
		}
		if (gameState == PAUSE) {
			window->clear();

			// Positionnez le rectangle de fond au coin supérieur gauche
			sf::View pauseCamera = CreateCamera(1);
			pauseCamera.setCenter(window->getSize().x / 2, window->getSize().y / 2);
			window->setView(pauseCamera);

			window->draw(*menu.GetBackground());

			menu.RenderMenu();
			window->display();
		}
		if (gameState == OPTION) {
			window->clear();
			sf::View OptionCam = CreateCamera(1);
			OptionCam.setCenter(window->getSize().x / 2, window->getSize().y / 2);
			window->setView(OptionCam);

			window->draw(*menu.GetBackground());

			menu.RenderMenu();
			window->display();
		}
	}
	save.Save(player , music);
}