#pragma once

#include <string>

class Entity;

class Component
{
public:
	
	Component(std::string name);
	~Component();

	std::string GetName();


	

	Entity* GetParent();
	void SetParent(Entity* parent);
private:

	std::string m_Name;

	Entity* m_Parent;
};

