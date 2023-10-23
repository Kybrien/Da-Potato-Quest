#pragma once
#include <vector>
#include "Maths/Vector2.h"
#include "Objects/Component.h"

class GameObject {
public:
	GameObject();
    GameObject(double x, double y, double sizeX, double sizeY);
    virtual ~GameObject();

    virtual void update(); // POUR PLUS TARD
    virtual void render(); // POUR PLUS TARD

    void addComponent(Component* component);
    void removeComponent(Component* component);

    void setPosition(double x, double y);
    void setSize(double x, double y);

    Vector2<double> getPosition();
    Vector2<double> getSize();
protected:
    Vector2<double> position, size;
    std::vector<Component*> components;
};