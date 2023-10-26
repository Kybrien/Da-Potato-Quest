#include "Scene.h"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Components/Sprite.h"
#include "Components/SquareCollider.h"

void Scene::Update()
{
	for (GameObject* const& gameObject : gameObjects)
	{
		gameObject->Update();
	}
}

void Scene::Render(sf::RenderWindow* _window)
{
	for (GameObject* const& gameObject : gameObjects)
	{
		gameObject->Render(_window);
	}
}

sf::View Scene::getGamera() {
	return camera;
}

void Scene::setCamera(sf::View newCamera) {
	camera = newCamera;
}

GameObject* Scene::CreateGameObject(const std::string& _name)
{
	auto gameObject = new GameObject();
	gameObject->SetName(_name);
	gameObjects.push_back(gameObject);
	return gameObject;
}

GameObject* Scene::CreateDummyGameObject(const std::string& name, float position, const std::string texture)
{
	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(Maths::Vector2f(position, position));

	SquareCollider* squareCollider = gameObject->CreateComponent<SquareCollider>();
	squareCollider->SetWidth(20.f);
	squareCollider->SetHeight(20.f);

	Sprite* sprite = new Sprite(texture);
	gameObject->AddComponent(sprite);

	return gameObject;
}
