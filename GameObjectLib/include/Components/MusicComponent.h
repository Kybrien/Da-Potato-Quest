#pragma once
#include <SFML/Audio/Music.hpp>
#include "Components/Component.h"

class MusicComponent : public Component
{
public:
    MusicComponent(GameObject* owner);
    ~MusicComponent() override;

    bool LoadMusic(const std::string& filePath);
    void Play(bool loop);
    void Pause();
    void Stop();
    void SetVolume(int Vol);
    void VolumePlus();
    void VolumeMoins();
    int GetVolume();
                      
private:
    sf::Music music;
    int MusicVolume = 100;
};