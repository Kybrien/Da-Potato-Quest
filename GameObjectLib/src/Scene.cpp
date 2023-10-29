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

void Scene::addCollider(SquareCollider* collider) {
	colliders.push_back(collider);
}

std::vector<SquareCollider*> Scene::getColliders() {
	return colliders;
}

GameObject* Scene::CreateGameObject(const std::string& _name)
{
	auto gameObject = new GameObject();
	gameObject->SetName(_name);
	gameObjects.push_back(gameObject);
	return gameObject;
}

GameObject* Scene::CreateDummyGameObject(const std::string& name, float position, const std::string texture, float scale)
{
	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(Maths::Vector2f(position, position));

	SquareCollider* squareCollider = gameObject->CreateComponent<SquareCollider>();
	squareCollider->SetWidth(12.0f);
	squareCollider->SetHeight(12.0f);

	Sprite* sprite = new Sprite(texture, scale);
	sprite->setOldPosition(gameObject->GetPosition());
	gameObject->AddComponent(sprite);

	return gameObject;
}
