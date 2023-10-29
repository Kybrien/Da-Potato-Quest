#include <iostream>
#include "SFML/Graphics.hpp"
#include <fstream>
#include "json.hpp"
#include "Maths/Vector2.h"
#include "Components/SquareCollider.h"
#include "Components/ShapeRenderer.h"
#include "Scene.h"

using json = nlohmann::json;

class TileMap : public sf::Drawable, public sf::Transformable
{
public:

    bool load(sf::Vector2u tileSize, const std::vector<int> tiles, unsigned int width, unsigned int height)
    {
        // on charge la texture du tileset
        if (!m_tileset.loadFromFile("assets/tilesets/tileset.png"))
            return false;

        // on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
        sf::VertexArray* layer_vertices = new sf::VertexArray;

        layer_vertices->setPrimitiveType(sf::Quads);
        layer_vertices->resize(width * height * 4);

        // on remplit le tableau de vertex, avec un quad par tuile
        for (unsigned int i = 0; i < width; ++i)
            for (unsigned int j = 0; j < height; ++j)
            {
                // on récupère le numéro de tuile courant
                int tileNumber = tiles[i + j * width] - 1;

                if (tileNumber >= 0) {

                    // on en déduit sa position dans la texture du tileset
                    int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
                    int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

                    // on récupère un pointeur vers le quad à définir dans le tableau de vertex
                    sf::Vertex* quad = &(*layer_vertices)[(i + j * width) * 4];

                    // on définit ses quatre coins
                    quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
                    quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                    quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
                    quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

                    // on définit ses quatre coordonnées de texture
                    quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
                    quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                    quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
                    quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
                }
            }

        m_layers.push_back(layer_vertices);

        return true;
    }

    bool addCollider(sf::Vector2u tileSize, const std::vector<int> tiles, unsigned int width, unsigned int height, Scene& scene) {
        for (unsigned int i = 0; i < width; ++i)
            for (unsigned int j = 0; j < height; ++j)
            {
                int tileNumber = tiles[i + j * width] - 1;

                if (tileNumber >= 0) {
                    tileNumber = 0;
                    GameObject* colliderobj = new GameObject;
                    colliderobj->SetPosition(Maths::Vector2f(i * tileSize.x, j * tileSize.y));
                    SquareCollider* collider = new SquareCollider;
                    collider->SetWidth(tileSize.x);
                    collider->SetHeight(tileSize.y);
                    colliderobj->AddComponent(collider);
                    scene.addCollider(collider);
                    std::cout << "Added collision. Size: " << collider->GetWidth() << " ; " << collider->GetHeight() << std::endl;
                }
            }

        return true;
    }

    bool loadmap(const std::string& tileset, Scene& scene) {
        std::ifstream mapf("assets/maps/" + tileset + ".json");
        json data = json::parse(mapf);

        //for (int i = 0; i < data["tilesets"].size(); i++) {
        //    sf::Texture* newTileset = new sf::Texture;
        //    std::string tilesetName = data["tilesets"][i]["name"];
        //    newTileset->loadFromFile("assets/tilesets/" + tilesetName + ".png");
        //    std::cout << "TILESET " + tilesetName + " LOADED SUCCESSFULLY." << std::endl;
        //}

        for (int i = 0; i < data["layers"].size(); i++) {
            if (data["layers"][i]["type"] == "tilelayer") {
                const std::vector<int> level = data["layers"][i]["data"];

                unsigned int width = data["layers"][i]["width"];
                unsigned int height = data["layers"][i]["height"];
                sf::Vector2u tileSize(16, 16);

                m_size.SetXY(width * 16, height * 16);

                if (data["layers"][i]["name"] != "Collision") {
                    load(tileSize, level, width, height);
                    std::cout << "LAYER " << data["layers"][i]["name"] << " LOADED SUCCESSFULLY." << std::endl;
                }
                else {
                    addCollider(tileSize, level, width, height, scene);
                    std::cout << "COLLISION LAYER " << data["layers"][i]["name"] << " LOADED SUCCESSFULLY." << std::endl;
                }
            }
        }

        return true;
    }

    int getWidth() {
        return m_size.x;
    }

    int getHeight() {
        return m_size.y;
    }

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // on applique la transformation
        states.transform *= getTransform();

        // on applique la texture du tileset
        states.texture = &m_tileset;

        // et on dessine enfin le tableau de vertex
        for (int i = 0; i < m_layers.size(); ++i) {
            // Appliquer la texture actuelle

            // Dessiner le vertexArray
            target.draw(*m_layers[i], states);
        }
    }

    std::vector<sf::VertexArray*> m_layers;
    sf::Texture m_tileset;
    Maths::Vector2<int> m_size = Maths::Vector2<int>(0, 0);
};