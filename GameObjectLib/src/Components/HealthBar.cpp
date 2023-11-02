#include "Components/HealthBar.h"
#include <iostream>

HealthBar::HealthBar(GameObject* Character, int maxHealth) : Character(Character), maxHealth(maxHealth), currentHealth(maxHealth) {
    heartTexture = new sf::Texture;
    if (!heartTexture->loadFromFile("assets/sprites/healthbar.png")) {
        // Gestion de l'erreur si le chargement échoue
    }
    heartSprite = new sf::Sprite(*heartTexture);
    heartSprite->setTextureRect(sf::IntRect(0, currentHealth * 32, 96, 32));
    heartSprite->setPosition(0 * heartSprite->getGlobalBounds().width, 0);

}


void HealthBar::SetHealth(int health) {
    currentHealth = health;
    if (currentHealth < 0) {
        currentHealth = 0;
    }
}

void HealthBar::LoseHeart() {
    if (currentHealth > 0) {
        currentHealth--;
    }
}

void HealthBar::Render(sf::RenderWindow* window) {
    window->draw(*heartSprite);
}


void HealthBar::Update() {
    heartSprite->setPosition(sf::Vector2f(Character->GetPosition().x, Character->GetPosition().y));
}