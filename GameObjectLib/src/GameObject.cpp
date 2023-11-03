#include "GameObject.h"

void GameObject::AddComponent(Component* _component)
{
	_component->SetOwner(this);
	components.push_back(_component);
}

void GameObject::RemoveComponent(Component* _component)
{
	components.erase(std::remove(components.begin(), components.end(), _component), components.end());
}

void GameObject::Update() const
{
	for (size_t i = 0; i < components.size(); i++)
	{
		components[i]->Update();
	}
}

void GameObject::Render(sf::RenderWindow* _window) const
{
	for (size_t i = 0; i < components.size(); i++)
	{
		components[i]->Render(_window);
	}
}

int GameObject::GetKill() {
	return this->killcount;
}

void GameObject::IncrementKill() {
	this->killcount++;
}

void GameObject::SetKill(int kill) {
	this->killcount = kill;
}