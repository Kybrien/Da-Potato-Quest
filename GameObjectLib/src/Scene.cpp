#include <iostream>

#include "Scene.h"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Components/Sprite.h"
#include "Components/SquareCollider.h"
#include "Components/Button.h"

void Scene::Update()
{
	for (GameObject* const& gameObject : gameObjects)
	{
		gameObject->Update();
	}

	if (player) {
		auto playerSprite = player->getComponent<Sprite>();
		auto playerCollider = player->getComponent<SquareCollider>();

		for (int i = 0; i < colliders.size(); i++) {
			if (SquareCollider::IsColliding(*playerCollider, *colliders[i])) {
				// G�rer les collisions horizontales et verticales s�par�ment
				float deltaX = playerCollider->GetOwner()->GetPosition().x - colliders[i]->GetOwner()->GetPosition().x;
				float deltaY = playerCollider->GetOwner()->GetPosition().y - colliders[i]->GetOwner()->GetPosition().y;

				if (abs(deltaX) > abs(deltaY)) {
					// Collision horizontale
					playerSprite->moveBack(0);
				}
				else {
					// Collision verticale
					playerSprite->moveBack(1);
				}
			}
		}
	}
}

void Scene::Render(sf::RenderWindow* _window)
{
	for (GameObject* const& gameObject : gameObjects)
	{
		gameObject->Render(_window);
	}
}

GameObject* Scene::getPlayer() {
	return player;
}

void Scene::setPlayer(GameObject* Player) {
	player = Player;
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

GameObject* Scene::CreateButtonGameObject(sf::RenderWindow* window, Maths::Vector2f position, Maths::Vector2f size, std::string text) {
	GameObject* gameObject = CreateGameObject("Button");
	gameObject->SetSPosition(window, position);

	Button* button = new Button(window, size, text);
	gameObject->AddComponent(button);

	return gameObject;
}