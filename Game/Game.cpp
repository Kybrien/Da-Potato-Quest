#include "Game.h"

#include ""

void Game::Init() {
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

	SaveComponent save(nullptr);
	save.LoadSave(player);

	Menu menu(window);
	menu.MainMenu();

	TileMap map;
	map.loadmap("Lvl01", scene);

	scene.setCamera(CreateCamera(window, 5));

	sf::Clock clock;
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
		}

		time = clock.restart();
		dt = time.asSeconds();

		ProcessInput(player, dt * speed, scene);

		scene.Update();
		HandleCamera(window, scene.getGamera(), player, map);
		window->clear(sf::Color::Black);
		window->draw(map);
		scene.Render(window);
		window->display();
	}
	save.Save(player);
}

void Game::Run() {

}