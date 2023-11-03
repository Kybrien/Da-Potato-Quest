#include "Components/SaveComponent.h"
#include "Components/MusicComponent.h"

SaveComponent::SaveComponent(GameObject* owner) : Component(owner) {}

SaveComponent::~SaveComponent() {}

void SaveComponent::LoadSave(GameObject* player , MusicComponent* music) {
    std::ifstream fichier(SavePath);
    // Vérifier si l'ouverture du fichier a réussi
    if (fichier.is_open()) {
        int rows = 0;
        std::string ligne;
        while (getline(fichier, ligne)) {
            std::istringstream lineValue(ligne);
            char comma;
            rows++;
            float x, y , vol;
            if (lineValue >> x >> comma >> y >> comma >> vol) {
                // Les valeurs ont été extraites avec succès
                Maths::Vector2<float> pos(x, y);
                player->SetPosition(pos);
                music->SetVolume(vol);
                std::cout << "volume set to" << vol << " actual vol = " << music->GetVolume();
            }
        }
        if (rows == 0) {
            Maths::Vector2<float> pos(352.0f, 160.0f);
            player->SetPosition(pos);
        }
        fichier.close();
    }
    else {
        Maths::Vector2<float> pos(352.0f, 160.0f);
        player->SetPosition(pos);
    }
}

void SaveComponent::Save(GameObject* player, MusicComponent* music) {
    std::ofstream fichier(SavePath);
    Maths::Vector2<float> pos = player->GetPosition();
    float x = pos.GetX();
    float y = pos.GetY();

    if (fichier.is_open()) {
        fichier << x << "," << y << "," << music->GetVolume() << "\n";
        fichier.close();
    }
    else {
        std::cout << "cant save" << std::endl;
    }
}

void SaveComponent::DelSave() {
    std::ofstream fichier(SavePath);
    if (fichier.is_open()) {
        fichier << "";
    }
    fichier.close();
}

