#pragma once

#include <string>
#include <map>

class Component;

class Entity
{
public:
	Entity();
	~Entity();

	void AddComponent(Component* component);

	template<typename T>
	T& GetComponent();
private:

	std::map<std::string, Component*> m_Components;
};

template<typename T>
T& Entity::GetComponent()
{
	return *static_cast<T*>(m_Components[T::GetName()]);
}