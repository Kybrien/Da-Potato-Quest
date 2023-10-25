#include "Scene.h"
#include <cstdlib>
#include "Components/Menu.h"
#include "Components/Button.h"
#include "GameObject.h"

Menu::Menu(sf::RenderWindow* _window) {
	//if (!font.loadFromFile(arial.ttf)) {
	//	//handle Error
	//}

	Scene menu;

	// Charger la texture de l'arrière-plan
	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("assets/images/background.png")) {
		// Gérer l'erreur si le chargement échoue
	}

	// Créer le rectangle de fond (background) avec la texture chargée
	sf::RectangleShape background(sf::Vector2f(_window->getSize().x, _window->getSize().y));
	background.setTexture(&backgroundTexture); // Appliquer la texture à la forme

	// Créer le premier bouton à partir du coin supérieur droit de l'écran
	GameObject* button1 = menu.CreateGameObject("bouton1");
	button1->SetPosition(Maths::Vector2f(1500, 230));

	Button* btncomponent1 = new Button("Bouton 1");
	button1->AddComponent(btncomponent1);

	// Créer le deuxième bouton en dessous du premier
	GameObject* button2 = menu.CreateGameObject("bouton2");
	button2->SetPosition(Maths::Vector2f(1500, 430));

	Button* btncomponent2 = new Button("Bouton 2");
	button2->AddComponent(btncomponent2);

	// Créer le troisième bouton en dessous du deuxième
	GameObject* button3 = menu.CreateGameObject("bouton3");
	button3->SetPosition(Maths::Vector2f(1500, 630));

	Button* btncomponent3 = new Button("Bouton 3");
	button3->AddComponent(btncomponent3);

	while (true) {
		menu.Update();

		sf::Event event;
		while (_window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				_window->close();
				return; 
			}

			if (event.type == sf::Event::MouseButtonPressed) {
				sf::Vector2f mousePos = _window->mapPixelToCoords(sf::Mouse::getPosition(*_window));

				// Vérifier si le bouton 1 est cliqué
				if (btncomponent1->IsClicked(mousePos)) {
					return;
				}

				// Vérifier si le bouton 2 est cliqué
				else if (btncomponent2->IsClicked(mousePos)) {
					// Faites quelque chose avec le bouton 2
				}

				// Vérifier si le bouton 3 est cliqué
				else if (btncomponent3->IsClicked(mousePos)) {
					_window->close();
					return;
					//quitte le programme
				}
			}
		}

		// Dessiner le fond
		_window->clear();
		_window->draw(background);

		menu.Render(_window);
		_window->display();
	}
}

Menu::~Menu() {

}