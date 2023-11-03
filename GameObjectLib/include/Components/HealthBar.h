#pragma once
#include "Component.h"
#include <SFML/Graphics.hpp>

class HealthBar : public Component {
public:
    HealthBar(GameObject* Character);
    void SetHealth(int health);
    void LoseHeart();
    void RenderGui(sf::RenderWindow* window);
    void Update() override;

private:
    GameObject* Character = nullptr;
    sf::Texture* heartTexture = nullptr;
    sf::Sprite* heartSprite = nullptr;
};