#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include "GameObject.h"

class Scene
{
public:
	Scene() = default;
	virtual ~Scene() = default;

	void Update();
	void Render(sf::RenderWindow* _window);

	sf::View getGamera();
	void setCamera(sf::View newCamera);

	GameObject* CreateGameObject(const std::string& _name);

	GameObject* CreateDummyGameObject(const std::string& name, float position, const std::string texture);

private:
	sf::View camera;
	std::vector<GameObject*> gameObjects;
};
