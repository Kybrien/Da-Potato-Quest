#pragma once
#include <memory>
#include <string>
#include <vector>

#include "Maths/Vector2.h"
#include "Components/Component.h"

class Component;

class GameObject
{
public:
	GameObject() = default;
	virtual ~GameObject() = default;

	std::string GetName() const { return name; }
	Maths::Vector2<float> GetPosition() const { return position; }

	void SetName(const std::string& _name) { name = _name; }
	void SetPosition(const Maths::Vector2<float>& _position) { position = _position; }
	void SetSPosition(sf::RenderWindow* window, const Maths::Vector2<float>& _position) {
		sf::Vector2u windowSize(window->getSize().x, window->getSize().y);

		position.x = windowSize.x * _position.x;
		position.y = windowSize.y * _position.y;
	}

	bool isActive() { return Active; }
	void setActive(bool state) { Active = state; }

	void AddComponent(Component* _component);

	template<typename T>
	T* CreateComponent()
	{
		T* component = new T();
		component->SetOwner(this);
		components.push_back(component);
		return component;
	}

	template <typename T>
	T* getComponent() {
		for (auto& component : components) {
			T* typedComponent = dynamic_cast<T*>(component);
			if (typedComponent != nullptr) {
				return typedComponent;
			}
		}
		return nullptr; // Retourne nullptr si le composant n'est pas trouvé
	}

	void RemoveComponent(Component* _component);
	void Update() const;
	void Render(sf::RenderWindow* _window) const;

private:
	std::string name = "GameObject";
	Maths::Vector2<float> position = Maths::Vector2f::Zero;
	std::vector<Component*> components;
	bool Active = true;
};
