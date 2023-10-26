#pragma once
#include <SFML/Audio/Music.hpp>
#include "Components/Component.h"

class MusicComponent : public Component
{
public:
    MusicComponent(GameObject* owner);
    ~MusicComponent();

    bool LoadMusic(const std::string& filePath);
    void Play(bool loop);
    void Pause();
    void Stop();

private:
    sf::Music music;
};