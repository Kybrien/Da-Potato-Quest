#pragma once

#include "components/component.h"
#include "GameObject.h"
#include <SFML/Audio/Music.hpp>

class MusicComponent : Component {
public:
	MusicComponent(GameObject* owner);
	~MusicComponent();

	void Update() override;
	void Render(sf::RenderWindow* _window) override;

	bool LoadMusic(const std::string& filepath);
	void Play();
	void Pause();
	void Stop();
private:
	sf::Music music;
};
