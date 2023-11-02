#include <iostream>
#include "Scene.h"
#include <cstdlib>
#include "Components/Menu.h"
#include "Components/Button.h"
#include "GameObject.h"

Menu::Menu(sf::RenderWindow* _window) {
	menuWindow = _window;
}

Menu::~Menu() {
	delete menu;
	delete background;
	for (int i = 0; i < buttons.size(); i++) {
		delete buttons[i];
	}
	buttons.clear();
}

void Menu::Close() {
	open = false;
	std::cout << "Buttons: " << buttons.size() << std::endl;
	//buttons.clear();
}

Scene Menu::Init() {
	menu = new Scene;
	background = new sf::RectangleShape;

	sf::Texture* mainMenuImage = new sf::Texture;
	if (!mainMenuImage->loadFromFile("assets/images/background.png")) {
		// G�rer l'erreur si le chargement �choue
	}

	sf::Texture* pauseMenuImage = new sf::Texture;
	if (!pauseMenuImage->loadFromFile("assets/images/PauseBackground.jpg")) {
		// G�rer l'erreur si le chargement �choue
	}

	backgroundImages.push_back(mainMenuImage);
	backgroundImages.push_back(pauseMenuImage);

	return *menu;
}

void Menu::CreateMainMenu() {
	background->setSize(sf::Vector2f(menuWindow->getSize().x, menuWindow->getSize().y));

	background->setTexture(backgroundImages[0], true);

	// Cr�er le premier bouton � partir du coin sup�rieur droit de l'�cran
	GameObject* button1 = menu->CreateButtonGameObject(menuWindow, Maths::Vector2f(0.7f, 0.3f), Maths::Vector2f(0.25f, 0.1f), "JOUER", sf::Color::Black);

	// Cr�er le deuxi�me bouton en dessous du premier
	GameObject* button2 = menu->CreateButtonGameObject(menuWindow, Maths::Vector2f(0.7f, 0.5f), Maths::Vector2f(0.25f, 0.1f), "OPTIONS", sf::Color::Black);

	// Cr�er le troisi�me bouton en dessous du deuxi�me
	GameObject* button3 = menu->CreateButtonGameObject(menuWindow, Maths::Vector2f(0.7f, 0.7f), Maths::Vector2f(0.25f, 0.1f), "QUITTER", sf::Color::Black);

	buttons.push_back(button1);
	buttons.push_back(button2);
	buttons.push_back(button3);
}

void Menu::CreatePauseMenu() {
	// Cr�er le deuxi�me bouton en dessous du premier
	GameObject* button1 = menu->CreateButtonGameObject(menuWindow, Maths::Vector2f(0.3f, 0.6f), Maths::Vector2f(0.05f, 0.3f), "REPRENDRE", sf::Color::White);

	// Cr�er le troisi�me bouton en dessous du deuxi�me
	GameObject* button2 = menu->CreateButtonGameObject(menuWindow, Maths::Vector2f(0.6f, 0.6f), Maths::Vector2f(0.05f, 0.3f), "MENU PRINCIPAL", sf::Color::White);

	button1->setActive(false);
	button2->setActive(false);

	buttons.push_back(button1);
	buttons.push_back(button2);
}

void Menu::MainMenu() {
	background->setSize(sf::Vector2f(menuWindow->getSize().x, menuWindow->getSize().y));

	background->setTexture(backgroundImages[0], true);

	buttons[0]->setActive(true);
	buttons[1]->setActive(true);
	buttons[2]->setActive(true);

	buttons[3]->setActive(false);
	buttons[4]->setActive(false);
}

void Menu::PauseMenu() {
	background->setSize(sf::Vector2f(menuWindow->getSize().x, menuWindow->getSize().y));

	background->setTexture(backgroundImages[1], true);

	buttons[0]->setActive(false);
	buttons[1]->setActive(false);
	buttons[2]->setActive(false);

	buttons[3]->setActive(true);
	buttons[4]->setActive(true);
}

void Menu::RenderMenu() {
	menu->Render(menuWindow);
}