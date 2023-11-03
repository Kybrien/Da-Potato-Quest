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
		// Gérer l'erreur si le chargement échoue
	}

	sf::Texture* pauseMenuImage = new sf::Texture;
	if (!pauseMenuImage->loadFromFile("assets/images/PauseBackground.jpg")) {
		// Gérer l'erreur si le chargement échoue
	}

	backgroundImages.push_back(mainMenuImage);
	backgroundImages.push_back(pauseMenuImage);

	return *menu;
}

void Menu::CreateMainMenu() {
	background->setSize(sf::Vector2f(menuWindow->getSize().x, menuWindow->getSize().y));

	background->setTexture(backgroundImages[0], true);

	// Créer le premier bouton à partir du coin supérieur droit de l'écran
	GameObject* button1 = menu->CreateButtonGameObject(menuWindow, Maths::Vector2f(0.7f, 0.3f), Maths::Vector2f(0.25f, 0.1f), "JOUER", sf::Color::White);

	// Créer le deuxième bouton en dessous du premier
	GameObject* button2 = menu->CreateButtonGameObject(menuWindow, Maths::Vector2f(0.7f, 0.5f), Maths::Vector2f(0.25f, 0.1f), "OPTIONS", sf::Color::White);

	// Créer le troisième bouton en dessous du deuxième
	GameObject* button3 = menu->CreateButtonGameObject(menuWindow, Maths::Vector2f(0.7f, 0.7f), Maths::Vector2f(0.25f, 0.1f), "QUITTER", sf::Color::White);

	buttons.push_back(button1);
	buttons.push_back(button2);
	buttons.push_back(button3);
}

void Menu::CreatePauseMenu() {
	// Créer le deuxième bouton en dessous du premier
	GameObject* button1 = menu->CreateButtonGameObject(menuWindow, Maths::Vector2f(0.3f, 0.6f), Maths::Vector2f(0.05f, 0.3f), "REPRENDRE", sf::Color::White);

	// Créer le troisième bouton en dessous du deuxième
	GameObject* button2 = menu->CreateButtonGameObject(menuWindow, Maths::Vector2f(0.6f, 0.6f), Maths::Vector2f(0.05f, 0.3f), "MENU PRINCIPAL", sf::Color::White);

	button1->setActive(false);
	button2->setActive(false);

	buttons.push_back(button1);
	buttons.push_back(button2);
}

void Menu::CreateOptionMenu() {
	GameObject* volPlus = menu->CreateButtonGameObject(menuWindow, Maths::Vector2f(0.7f, 0.3f), Maths::Vector2f(0.05f, 0.05f), "UP", sf::Color::White);
	GameObject* vol = menu->CreateButtonGameObject(menuWindow, Maths::Vector2f(0.75f, 0.3f), Maths::Vector2f(0.05f, 0.05f), "Vol", sf::Color::White);
	GameObject* volMoins = menu->CreateButtonGameObject(menuWindow, Maths::Vector2f(0.82f, 0.3f), Maths::Vector2f(0.05f, 0.05f), "Down", sf::Color::White);
	GameObject* DelSave = menu->CreateButtonGameObject(menuWindow, Maths::Vector2f(0.76f, 0.3f), Maths::Vector2f(0.05f, 0.3f), "Delete Save", sf::Color::White);
	GameObject* Close = menu->CreateButtonGameObject(menuWindow, Maths::Vector2f(0.76f, 0.4f), Maths::Vector2f(0.05f, 0.3f), "Close", sf::Color::White);

	volPlus->setActive(false);
	vol->setActive(false);
	volMoins->setActive(false);
	DelSave->setActive(false);
	Close->setActive(false);

	buttons.push_back(volPlus);
	buttons.push_back(vol);
	buttons.push_back(volMoins);
	buttons.push_back(DelSave);
	buttons.push_back(Close);
}

void Menu::MainMenu() {
	background->setSize(sf::Vector2f(menuWindow->getSize().x, menuWindow->getSize().y));

	background->setTexture(backgroundImages[0], true);

	buttons[0]->setActive(true);
	buttons[1]->setActive(true);
	buttons[2]->setActive(true);

	buttons[3]->setActive(false);
	buttons[4]->setActive(false);
	buttons[5]->setActive(false);
	buttons[6]->setActive(false);
	buttons[7]->setActive(false);
	buttons[8]->setActive(false);
	buttons[9]->setActive(false);
}

void Menu::PauseMenu() {
	background->setSize(sf::Vector2f(menuWindow->getSize().x, menuWindow->getSize().y));

	background->setTexture(backgroundImages[1], true);

	buttons[0]->setActive(false);
	buttons[1]->setActive(false);
	buttons[2]->setActive(false);
	buttons[5]->setActive(false);
	buttons[6]->setActive(false);
	buttons[7]->setActive(false);
	buttons[8]->setActive(false);
	buttons[9]->setActive(false);

	buttons[3]->setActive(true);
	buttons[4]->setActive(true);
}

void Menu::OptionMenu() {
	background->setSize(sf::Vector2f(menuWindow->getSize().x, menuWindow->getSize().y));

	background->setTexture(backgroundImages[0], true);

	buttons[0]->setActive(false);
	buttons[1]->setActive(false);
	buttons[2]->setActive(false);
	buttons[3]->setActive(false);
	buttons[4]->setActive(false);

	buttons[5]->setActive(true);
	buttons[6]->setActive(true);
	buttons[7]->setActive(true);
	buttons[8]->setActive(true);
	buttons[9]->setActive(true);
}

void Menu::RenderMenu() {
	menu->Render(menuWindow);
}