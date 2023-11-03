#pragma once
#include "SFML/Graphics.hpp"
#include "GameObject.h"
#include "Scene.h"
#include "TileMap.h"
#include "Components/Button.h"
#include "Components/MusicComponent.h"

class Game {
public:
	enum GAME_STATES { MAIN_MENU, PLAYING, PAUSE , OPTION };
	void Init();
	void Run();

	void ProcessInput(GameObject* player, float dt, Scene scene);
	void FollowPlayer(GameObject* ennemie, float dt, Scene scene);

	void HandleCamera(sf::View camera, GameObject* player, TileMap map);
	sf::View CreateCamera(float zoom);
private:
	sf::RenderWindow* window = nullptr;
	Scene scene;
	GameObject* player = nullptr;
	GameObject* weapon = nullptr;
	GameObject* healthbar = nullptr;
	GameObject* achievement = nullptr;
	std::vector<GameObject*> enemies;
	std::vector<MusicComponent*> sounds;
	bool isPaused = false;
	int gameState = 0; //0 = Main Menu; 1 = Playing; 2 = Pause
};