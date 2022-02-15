#include "Entity.h"

void Tmpl8::Entity::SwitchSprite()
{

	Sprite* tempsprite = m_TheEntity;
	m_TheEntity = m_DeathSprite;
	m_DeathSprite = tempsprite;
	tempsprite = nullptr;
	delete tempsprite;
}
