#pragma once

class Component {
protected:
    GameObject* owner;
public:
    Component(GameObject* owner) {
        this->owner = owner;
    }
    virtual ~Component() {}
    virtual void update() = 0;
};