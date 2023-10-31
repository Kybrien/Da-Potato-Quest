#include <iostream>
#include "Scene.h"
#include <cstdlib>
#include "Components/Menu.h"
#include "Components/Button.h"
#include "GameObject.h"
#include <string>

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

	// Charger la texture de l'arri�re-plan
	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("assets/images/background.png")) {
		// G�rer l'erreur si le chargement �choue
	}

	// Cr�er le rectangle de fond (background) avec la texture charg�e
	sf::RectangleShape background(sf::Vector2f(menuWindow->getSize().x, menuWindow->getSize().y));
	background.setTexture(&backgroundTexture); // Appliquer la texture � la forme

	// Cr�er le premier bouton � partir du coin sup�rieur droit de l'�cran
	GameObject* button1 = menu->CreateButtonGameObject(menuWindow, Maths::Vector2f(0.7f, 0.3f), Maths::Vector2f(0.25f, 0.1f), "JOUER");

	// Cr�er le deuxi�me bouton en dessous du premier
	GameObject* button2 = menu->CreateButtonGameObject(menuWindow, Maths::Vector2f(0.7f, 0.5f), Maths::Vector2f(0.25f, 0.1f), "OPTIONS");

	// Cr�er le troisi�me bouton en dessous du deuxi�me
	GameObject* button3 = menu->CreateButtonGameObject(menuWindow, Maths::Vector2f(0.7f, 0.7f), Maths::Vector2f(0.25f, 0.1f), "QUITTER");

	while (open) {
		menu->Update();

		sf::Event event;
		while (menuWindow->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				menuWindow->close();
				Close();
			}

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					// Mettre en pause ou reprendre le jeu
					isGamePaused = !isGamePaused;
					isMenuActive = isGamePaused; // Activer le menu si le jeu est en pause
				}
			}
		}


		if (!isGamePaused){
			if (event.type == sf::Event::MouseButtonPressed) {
				sf::Vector2f mousePos = menuWindow->mapPixelToCoords(sf::Mouse::getPosition(*menuWindow));

				// V�rifier si le bouton 1 est cliqu�
				if (button1->getComponent<Button>()->IsClicked(mousePos)) {
					Close();
				}
				if (button2->getComponent<Button>()->IsClicked(mousePos)) {
					//Options
				}
				if (button3->getComponent<Button>()->IsClicked(mousePos)) {
					Close();
				}
			}
		}

		// Dessiner le fond
		menuWindow->clear();
		menuWindow->draw(background);

		// Afficher le menu pause si le jeu est en pause
		if (isMenuActive) {
			if (event.type == sf::Event::MouseButtonPressed) {
				sf::Vector2f mousePos = menuWindow->mapPixelToCoords(sf::Mouse::getPosition(*menuWindow));

				// V�rifier si le bouton 1 est cliqu�
				if (button1->getComponent<Button>()->IsClicked(mousePos)) {
					Close();
					isGamePaused = !isGamePaused;
				}
				if (button2->getComponent<Button>()->IsClicked(mousePos)) {
					//Options
				}
				if (button3->getComponent<Button>()->IsClicked(mousePos)) {
					Close();
				}
			}
			sf::Texture backgroundTexture;
			if (!backgroundTexture.loadFromFile("assets/images/background.png")) {
				// G�rer l'erreur si le chargement �choue
			}

			// Cr�er le rectangle de fond (background) avec la texture charg�e
			sf::RectangleShape background(sf::Vector2f(menuWindow->getSize().x, menuWindow->getSize().y));
			background.setTexture(&backgroundTexture); // Appliquer la texture � la forme

		}
		else {
			menu->Render(menuWindow);
		}

		menuWindow->display();
	}

	return *menu;
}

