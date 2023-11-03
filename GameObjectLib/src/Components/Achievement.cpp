#include <iostream>
#include <string>
#include "Components/Achievement.h"
#include "Components/Sprite.h"

Achievement::Achievement(GameObject* Character , std::string message) : Character(Character) {
    int Kills = Character->GetKill();
    textAchievement->setString(message);
    textAchievement->setCharacterSize(25);
    textAchievement->setFillColor(sf::Color::White);
    if (!AchievementFont->loadFromFile("assets/fonts/alagard.ttf")) {
        std::cout << "font error" << std::endl;
    }
    textAchievement->setFont(*AchievementFont);
}

void Achievement::RenderGui(sf::RenderWindow* window) {
    sf::View guiView;
    guiView.setSize(window->getSize().x, window->getSize().y);
    guiView.setCenter(window->getSize().x / 2, window->getSize().y / 2);
    window->setView(guiView);

    textAchievement->setPosition(500, 0);

    window->draw(*textAchievement);
}