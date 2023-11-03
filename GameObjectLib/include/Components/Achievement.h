#pragma once
#include "Component.h"
#include <SFML/Graphics.hpp>

class Achievement : public Component {
public:
    Achievement(GameObject* Character , std::string message);
    void RenderGui(sf::RenderWindow* window);

private:
    GameObject* Character = nullptr;
    sf::Text* textAchievement = new sf::Text;
    sf::Font* AchievementFont = new sf::Font;
};