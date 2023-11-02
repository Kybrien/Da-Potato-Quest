#pragma once
#include "Component.h"
#include <SFML/Graphics.hpp>

class HealthBar : public Component {
public: 
    HealthBar(GameObject* Character, int maxHealth);
    void SetHealth(int health);
    void LoseHeart();
    void Render(sf::RenderWindow* window) override;
    void Update() override;

private:
    GameObject* Character = nullptr;
    int maxHealth;
    int currentHealth;
    sf::Texture* heartTexture = nullptr;
    sf::Sprite* heartSprite = nullptr;
};
