#include <iostream>
#include <SFML/Graphics.hpp>
#include "Maths/Vector2.h"
#include "Objects/Sprite.h"
#include "DataStructures/Container.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "SFML works!");

    GameObject* testSprite = new GameObject(0, 0, 10, 10);
    Sprite* spriteComponent = new Sprite(testSprite, "potato.png");
    testSprite->addComponent(spriteComponent);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                spriteComponent->Move(Vector2<double>::left);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                //sprite.move(-1, 0);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                //sprite.move(-1, 0);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                //sprite.move(-1, 0);
            }
        }

        window.clear();
        window.draw(spriteComponent->sprite);
        window.display();
    }

    return 0;
}