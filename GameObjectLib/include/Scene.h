#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include "GameObject.h"
#include "Components/SquareCollider.h"

class Scene
{
public:
	Scene() = default;
	virtual ~Scene() = default;

	void Update();
	void Render(sf::RenderWindow* _window);

	GameObject* getPlayer();
	void setPlayer(GameObject* Player);

	std::vector<GameObject*> getGameObjects() { return gameObjects; }

	sf::View getCamera();
	void setCamera(sf::View newCamera);

	void addCollider(SquareCollider* collider);
	std::vector<SquareCollider*> getColliders();

	GameObject* CreateGameObject(const std::string& _name);

	GameObject* CreateWeaponGameObject(sf::RenderWindow* window, const std::string& _name, GameObject* player, int damage);

	GameObject* CreateDummyGameObject(const std::string& name, float position, const std::string texture, float scale);

	GameObject* CreateButtonGameObject(sf::RenderWindow* window, Maths::Vector2f position, Maths::Vector2f size, std::string text, sf::Color color);

private:
	GameObject* player = nullptr;
	sf::View camera;
	std::vector<GameObject*> gameObjects;
	std::vector<SquareCollider*> colliders;
};
