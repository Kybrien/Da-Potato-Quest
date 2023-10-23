#pragma once
#include "Component.h"
#include "Objects/GameObject.h"
#include "Maths/Vector2.h"

class Collider : public Component {
public:
    GameObject* owner;
    enum Shape { SQUARE, CIRCLE };

    Collider(GameObject* owner, Shape shape, double size);

    // Méthode pour détecter les collisions avec un autre Collider
    bool isColliding(const Collider& other);

private:
    Shape shape;
    double size;
    // D'autres membres et méthodes nécessaires, y compris la position du Collider.

    double calculateDistance(const Vector2<double>& a, const Vector2<double>& b);
};