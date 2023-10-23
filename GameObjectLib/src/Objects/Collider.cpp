#include "Objects/Collider.h"
#include "Objects/GameObject.h"
#include <cmath>

Collider::Collider(GameObject* owner, Shape shape, double size) : shape(shape), size(size) {
    this->owner = owner;
}

bool Collider::isColliding(const Collider& other) {
    GameObject* otherGO = other.owner;

    if (shape == SQUARE && other.shape == SQUARE) {

        double thisLeft = owner->getPosition().x;
        double thisRight = owner->getPosition().x + size;
        double thisTop = owner->getPosition().y;
        double thisBottom = owner->getPosition().y + size;

        double otherLeft = otherGO->getPosition().x;
        double otherRight = otherGO->getPosition().x + other.size;
        double otherTop = otherGO->getPosition().y;
        double otherBottom = otherGO->getPosition().y + other.size;

        // Vérifiez si les deux rectangles se chevauchent
        if (thisRight >= otherLeft && thisLeft <= otherRight && thisBottom >= otherTop && thisTop <= otherBottom) {
            return true;  // Il y a collision
        }
    }
    else if (shape == CIRCLE && other.shape == CIRCLE) {
        // Collision entre deux cercles
        double distance = (owner->getPosition() - otherGO->getPosition()).magnitude();
        double radiusSum = size / 2 + other.size / 2;
        return distance < radiusSum;
    }

    return false;
}