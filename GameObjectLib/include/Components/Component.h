#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Audio/Music.hpp>

#include "GameObject.h"

class GameObject;

class Component
{
public:
	Component() = default;
	Component(GameObject* owner);
	virtual ~Component() = default;

	virtual void Update();
	virtual void Render(sf::RenderWindow* _window);

	GameObject* GetOwner() const { return owner; }
	void SetOwner(GameObject* _owner) { owner = _owner; }

private:
	GameObject* owner = nullptr;
};

class MusicComponent : public Component
{
public:
    MusicComponent(GameObject* owner);
    ~MusicComponent();

    void Update() override;
    void Render(sf::RenderWindow* _window) override;

    bool LoadMusic(const std::string& filePath);
    void Play();
    void Pause();
    void Stop();

private:
    sf::Music music;
};
