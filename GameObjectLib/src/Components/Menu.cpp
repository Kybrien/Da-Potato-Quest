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
}

void Menu::Close() {
	open = false;
}

Scene Menu::MainMenu() {
	menu = new Scene;

	// Charger la texture de l'arrière-plan
	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("assets/images/background.png")) {
		// Gérer l'erreur si le chargement échoue
	}

	// Créer le rectangle de fond (background) avec la texture chargée
	sf::RectangleShape background(sf::Vector2f(menuWindow->getSize().x, menuWindow->getSize().y));
	background.setTexture(&backgroundTexture); // Appliquer la texture à la forme

	// Créer le premier bouton à partir du coin supérieur droit de l'écran
	GameObject* button1 = menu->CreateButtonGameObject(menuWindow, Maths::Vector2f(0.7f, 0.3f), Maths::Vector2f(0.25f, 0.1f), "JOUER");

	// Créer le deuxième bouton en dessous du premier
	GameObject* button2 = menu->CreateButtonGameObject(menuWindow, Maths::Vector2f(0.7f, 0.5f), Maths::Vector2f(0.25f, 0.1f), "OPTIONS");

	// Créer le troisième bouton en dessous du deuxième
	GameObject* button3 = menu->CreateButtonGameObject(menuWindow, Maths::Vector2f(0.7f, 0.7f), Maths::Vector2f(0.25f, 0.1f), "QUITTER");

	while (open) {
		menu->Update();

		sf::Event event;
		while (menuWindow->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				menuWindow->close();
				Close();
			}

			if (event.type == sf::Event::MouseButtonPressed) {
				sf::Vector2f mousePos = menuWindow->mapPixelToCoords(sf::Mouse::getPosition(*menuWindow));

				// Vérifier si le bouton 1 est cliqué
				if (button1->getComponent<Button>()->IsClicked(mousePos)) {
					Close();
				}

				// Vérifier si le bouton 2 est cliqué
				else if (button2->getComponent<Button>()->IsClicked(mousePos)) {
					// Faites quelque chose avec le bouton 2
				}

				// Vérifier si le bouton 3 est cliqué
				else if (button3->getComponent<Button>()->IsClicked(mousePos)) {
					menuWindow->close();
					Close();
					//quitte le programme
				}
			}
		}

		// Dessiner le fond
		menuWindow->clear();
		menuWindow->draw(background);

		menu->Render(menuWindow);
		menuWindow->display();
	}

	return *menu;
}