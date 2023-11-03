#include <iostream>

#include "Scene.h"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Components/Sprite.h"
#include "Components/SquareCollider.h"
#include "Components/Button.h"
#include "Components/Weapon.h"

void Scene::Update()
{
	for (GameObject* const& gameObject : gameObjects)
	{
		if (gameObject != nullptr)
			gameObject->Update();
	}

	if (player) {
		auto playerSprite = player->getComponent<Sprite>();
		auto playerCollider = player->getComponent<SquareCollider>();

		for (int i = 0; i < colliders.size(); i++) {
			if (SquareCollider::IsColliding(*playerCollider, *colliders[i])) {
				// Gérer les collisions horizontales et verticales séparément
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
		if (gameObject->isActive() && gameObject != nullptr) {
			gameObject->Render(_window);
		}
	}
}

GameObject* Scene::getPlayer() {
	return player;
}

void Scene::setPlayer(GameObject* Player) {
	player = Player;
}

sf::View Scene::getCamera() {
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

GameObject* Scene::CreateWeaponGameObject(sf::RenderWindow* window, const std::string& _name, GameObject* player, int damage)
{
	auto gameObject = new GameObject();
	gameObject->SetName(_name);
	gameObjects.push_back(gameObject);

	SquareCollider* squareCollider = gameObject->CreateComponent<SquareCollider>();
	squareCollider->SetWidth(16.0f);
	squareCollider->SetHeight(16.0f);

	Weapon* weapon = new Weapon(window, player, "slash", damage);
	gameObject->AddComponent(weapon);

	return gameObject;
}

GameObject* Scene::CreateDummyGameObject(const std::string& name, float position, const std::string texture, int maxHealth, float scale)
{
	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(Maths::Vector2f(position, position));

	SquareCollider* squareCollider = gameObject->CreateComponent<SquareCollider>();
	squareCollider->SetWidth(12.0f);
	squareCollider->SetHeight(12.0f);

	Sprite* sprite = new Sprite(texture, maxHealth, scale);
	sprite->setOldPosition(gameObject->GetPosition());
	sprite->getSprite()->setTextureRect(sf::IntRect(sprite->getAnimation().x * 32, sprite->getAnimation().y * 32, 32, 32));
	gameObject->AddComponent(sprite);

	return gameObject;
}

GameObject* Scene::CreateButtonGameObject(sf::RenderWindow* window, Maths::Vector2f position, Maths::Vector2f size, std::string text, sf::Color color) {
	GameObject* gameObject = CreateGameObject("Button");
	gameObject->SetSPosition(window, position);

	Button* button = new Button(window, size, text, color);
	gameObject->AddComponent(button);

	return gameObject;
}