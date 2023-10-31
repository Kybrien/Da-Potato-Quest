#include "Components/MusicComponent.h"

MusicComponent::MusicComponent(GameObject* owner) : Component(owner) {}

MusicComponent::~MusicComponent() {}

bool MusicComponent::LoadMusic(const std::string& filePath)
{
    return music.openFromFile("assets/music/" + filePath);
}

void MusicComponent::Play(bool loop)
{
    music.play();
    music.setLoop(loop);  // Jouer en boucle
}

void MusicComponent::Pause()
{
    music.pause();
}

void MusicComponent::Stop()
{
    music.stop();
}

void MusicComponent::SetVolume(int Vol) {
    music.setVolume(Vol);
}

void MusicComponent::VolumePlus()
{
    if (MusicVolume != 100) {
        MusicVolume += 10;
        SetVolume(MusicVolume);
    }
}

void MusicComponent::VolumeMoins()
{
    if (MusicVolume != 0) {
        MusicVolume -= 10;
        SetVolume(MusicVolume);
    }
}

int MusicComponent::GetVolume() {
    return MusicVolume;
}
