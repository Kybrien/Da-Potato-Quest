#pragma once
#include "Component.h"
#include "Objects/GameObject.h"
#include "Maths/Vector2.h"

class Collider : public Component {
public:
    enum Shape { SQUARE, CIRCLE };

    Collider(GameObject* owner, Shape shape, double size) : Component(owner) {}

    // Méthode pour détecter les collisions avec un autre Collider
    bool isColliding(const Collider& other);

private:
    Shape shape;
    double size;
};