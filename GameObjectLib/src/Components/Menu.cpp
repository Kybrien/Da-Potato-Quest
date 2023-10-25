#include "Scene.h"
#include "Components/Menu.h"
#include "Components/Button.h"
#include "GameObject.h"

Menu::Menu(sf::RenderWindow* _window) {
	//if (!font.loadFromFile(arial.ttf)) {
	//	//handle Error
	//}

	Scene menu;

	GameObject* button1 = menu.CreateGameObject("boutton1");
	button1->SetPosition(Maths::Vector2f(50, 200));

	Button* btncomponent = new Button("test");
	button1->AddComponent(btncomponent);

	while (true) {
		menu.Update();
		_window->clear(sf::Color::Black);
		menu.Render(_window);
		_window->display();
	}
}

Menu::~Menu() {

}