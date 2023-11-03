#include <iostream>
#include "Components/HealthBar.h"
#include "Components/Sprite.h"

HealthBar::HealthBar(GameObject* Character) : Character(Character) {
    int currentHealth = Character->getComponent<Sprite>()->getCurrentHealth();
    heartTexture = new sf::Texture;
    if (!heartTexture->loadFromFile("assets/sprites/healthbar.png")) {
        // Gestion de l'erreur si le chargement échoue
    }
    heartSprite = new sf::Sprite(*heartTexture);
    heartSprite->setScale(2, 2);
    heartSprite->setTextureRect(sf::IntRect(0, currentHealth * 32, 96, 32));
    heartSprite->setPosition(0 * heartSprite->getGlobalBounds().width, 0);

}


void HealthBar::SetHealth(int health) {
    int currentHealth = Character->getComponent<Sprite>()->getCurrentHealth();
    currentHealth = health;
    if (currentHealth < 0) {
        currentHealth = 0;
    }
}

void HealthBar::LoseHeart() {
    int currentHealth = Character->getComponent<Sprite>()->getCurrentHealth();
    if (currentHealth > 0) {
        currentHealth--;
    }
}

void HealthBar::RenderGui(sf::RenderWindow* window) {
    sf::View guiView;
    guiView.setSize(window->getSize().x, window->getSize().y);
    guiView.setCenter(window->getSize().x / 2, window->getSize().y / 2);
    window->setView(guiView);

    heartSprite->setPosition(0, 0);

    window->draw(*heartSprite);
}


void HealthBar::Update() {
    int currentHealth = Character->getComponent<Sprite>()->getCurrentHealth();
    heartSprite->setTextureRect(sf::IntRect(0, currentHealth * 32, 96, 32));
}