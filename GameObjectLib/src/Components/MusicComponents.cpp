#include "components/component.h"

MusicComponent::MusicComponent(GameObject* owner) : Component(owner) {}

MusicComponent::~MusicComponent() {}

bool MusicComponent::LoadMusic(const std::string& filePath)
{
    return music.openFromFile("resources/" + filePath);
}

void MusicComponent::Play()
{
    music.play();
    music.setLoop(true);  // Jouer en boucle
}

void MusicComponent::Pause()
{
    music.pause();
}

void MusicComponent::Stop()
{
    music.stop();
}

void MusicComponent::Update()
{
    // Ajoutez ici la logique de mise à jour de la musique si nécessaire
}

void MusicComponent::Render(sf::RenderWindow* _window)
{
    // Ajoutez ici la logique de rendu de la musique si nécessaire
}