#include "Entity.h"

#include "Component.h"
#include "Transform.h"

#include <iostream>

Entity::Entity()
{
	AddComponent(new Transform({ 0., 0., 0. }, { 0., 0., 0. }, { 1., 1., 1. }));
}

Entity::~Entity()
{
	for (std::map<std::string, Component*>::iterator itr = m_Components.begin(); itr != m_Components.end(); itr++)
	{
		delete (itr->second);
		(itr->second) = nullptr;
	}
	m_Components.clear();
}

void Entity::AddComponent(Component* component)
{
	if (m_Components.find(component->GetName()) != m_Components.end())
	{
		std::cout << "This component is already attached to this entity!" << std::endl;
		return;
	}
	component->SetParent(this);
	m_Components[component->GetName()] = component;
}