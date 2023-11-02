#include <iostream>
#include "Scene.h"
#include <cstdlib>
#include "Components/Pause.h"
#include "Components/Button.h"
#include "GameObject.h"

Pause::Pause(sf::RenderWindow* _window) {
	menuWindow = _window;
}

Pause::~Pause() {
	delete menu;
}

void Pause::Close() {
	open = false;
}

Scene Pause::InitPause() {
	menu = new Scene;
	background = new sf::Texture;
	// Charger la texture de l'arrière-plan
	if (!background->loadFromFile("assets/images/Pausebackground.png")) {
		// Gérer l'erreur si le chargement échoue
	}

	// Créer le rectangle de fond (background) avec la texture chargée
	sf::RectangleShape backgroundShape(sf::Vector2f(menuWindow->getSize().x, menuWindow->getSize().y));
	backgroundShape.setTexture(background); // Appliquer la texture à la forme

	// Créer le deuxième bouton en dessous du premier
	GameObject* button2 = menu->CreateButtonGameObject(menuWindow, Maths::Vector2f(0.3f, 0.6f), Maths::Vector2f(0.05f, 0.3f), "OPTIONS");

	// Créer le troisième bouton en dessous du deuxième
	GameObject* button3 = menu->CreateButtonGameObject(menuWindow, Maths::Vector2f(0.5f, 0.6f), Maths::Vector2f(0.05f, 0.3f), "QUITTER");

	return *menu;
}

void Pause::CreatePauseMenu() {
	// Créer le rectangle de fond (background) avec la texture chargée
	sf::RectangleShape backgroundShape(sf::Vector2f(menuWindow->getSize().x, menuWindow->getSize().y));
	backgroundShape.setTexture(background); // Appliquer la texture à la forme

	// Créer le deuxième bouton en dessous du premier
	GameObject* button2 = menu->CreateButtonGameObject(menuWindow, Maths::Vector2f(0.3f, 0.6f), Maths::Vector2f(0.05f, 0.3f), "OPTIONS");

	// Créer le troisième bouton en dessous du deuxième
	GameObject* button3 = menu->CreateButtonGameObject(menuWindow, Maths::Vector2f(0.5f, 0.6f), Maths::Vector2f(0.05f, 0.3f), "QUITTER");

	buttons.push_back(button2);
	buttons.push_back(button3);
}

void Pause::RenderPauseMenu() {
	menu->Render(menuWindow);
}