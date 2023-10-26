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