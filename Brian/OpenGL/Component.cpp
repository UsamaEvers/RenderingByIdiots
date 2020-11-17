#include "Component.h"

#include "Entity.h"

Component::Component(std::string name)
	: m_Name(name)
	, m_Parent(nullptr)
{
}

Component::~Component()
{
	m_Parent = nullptr;
}

std::string Component::GetName()
{
	return m_Name;
}

Entity* Component::GetParent()
{
	return m_Parent;
}

void Component::SetParent(Entity* parent)
{
	m_Parent = parent;
}