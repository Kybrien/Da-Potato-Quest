#include <iostream>
#include "Objects/GameObject.h"
#include "DataStructures/Container.h"

GameObject::GameObject() : position(Vector2<double>(0, 0)), size(Vector2<double>(0, 0)) {}

GameObject::GameObject(double x, double y, double sizeX, double sizeY) {
    this->position = Vector2<double>(x, y);
    this->size = Vector2<double>(sizeX, sizeY);
}

GameObject::~GameObject() {
    for (Component* component : components) {
        delete component;
    }
}

void GameObject::update() {
    for (Component* component : components) {
        component->update();
    }
}

void GameObject::render() {
    std::cout << "Rendering GameObject at (" << this->position.x << ", " << this->position.y << ")" << std::endl;
}

void GameObject::addComponent(Component* component) {
    components.push_back(component);
}

void GameObject::removeComponent(Component* component) {
    auto component_index = std::find(components.begin(), components.end(), component);
    if (component_index != components.end()) {
        components.erase(component_index);
        delete component;
    }

}

void GameObject::setPosition(double x, double y) {
    this->position = Vector2<double>(x, y);
}

void GameObject::setSize(double x, double y) {
    this->size = Vector2<double>(x, y);
}

Vector2<double> GameObject::getPosition() {
    return Vector2<double>(this->position.x, this->position.y);
}

Vector2<double> GameObject::getSize() {
    return Vector2<double>(this->size.x, this->size.y);
}