#pragma once
#include "Components/Component.h"
#include "Components/MusicComponent.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class SaveComponent : Component {
public:
	SaveComponent(GameObject* owner);
	~SaveComponent() override;

	void LoadSave(GameObject* player , MusicComponent* music);
	void Save(GameObject* player , MusicComponent* music);
	void DelSave();
private:
	std::string SavePath = "assets/save/Save(DontModifyItLittleCheater).txt";
};
