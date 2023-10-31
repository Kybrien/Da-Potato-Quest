#pragma once
#include "Components/Component.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class SaveComponent : Component {
public:
	SaveComponent(GameObject* owner);
	~SaveComponent() override;

	void LoadSave(GameObject* player);
	void Save(GameObject* player);
private:
	std::string SavePath = "assets/save/Save(DontModifyItLittleCheater).txt";
};
