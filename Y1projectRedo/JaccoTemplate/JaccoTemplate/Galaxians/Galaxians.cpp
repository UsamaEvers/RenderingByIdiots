#include "Galaxians.h"
#include "GalaxianUI.h"
#include "GalaxianPlayer.h"
#include "AlienManager.h"
#include "Alien.h"
#include "Background.h"
#include "../template/Entity.h"
#include "../template/Surface.h"
#include "../template/Input.h"
#include "Missile.h"
namespace Tmpl8 {

	bool Galaxians::Init(Surface* screen)
	{
		//Init alienmanager
		m_TheAlienManager = new AlienManager();
		m_ThePlayer = new GalaxianPlayer(screen);
		m_TheAlienManager->Init(screen, m_ThePlayer, m_AllEntitiesArray, 0);

		//init Player and Missile
		Missile* themissile = new Missile(m_TheAlienManager->GetAlienArray());
		m_ThePlayer->Init(screen, themissile);
		m_AllEntitiesArray[60] = m_ThePlayer;
		m_TheUI = new GalaxianUI();
		m_Background = new Background(screen);
		m_TheUI->Init(screen,m_ThePlayer->GetHealth());
		return true;
	}
	bool Galaxians::Update(Surface* screen, float dt)
	{
		MainMenuHandler(dt);
		CheckAlienPlayerCollision();
		m_Background->Update(screen, dt);
		m_TheUI->Update(m_CurrentGameState, dt,m_ThePlayer->GetPlayerScore());
		m_TheUI->UpdatePlayerHealth(m_ThePlayer->GetHealth());

		if (GalaxiansGameEnum::GameActiveState == m_CurrentGameState)
		{
			m_TheAlienManager->Update(screen, dt);
			for (int i = 0; i < 61; i++)
			{
				if (nullptr == m_AllEntitiesArray[i])
					break;
				m_AllEntitiesArray[i]->Update(dt);
			}
			return true;
		}
		
	}
	bool Galaxians::Draw(Surface* screen)
	{
		m_TheUI->Draw(screen);
		m_Background->Draw(screen);

		if (GalaxiansGameEnum::GameActiveState == m_CurrentGameState)
		{
			for (int i = 0; i < 61; i++)
			{
				if (nullptr == m_AllEntitiesArray[i])
					break;
				m_AllEntitiesArray[i]->Draw(screen);
			}
			return true;
		}
	}

	void Galaxians::CheckAlienPlayerCollision()
	{
		for (int i = 0; i < 60; i++)
		{
			//only check the diving aliens for collision
			if (m_TheAlienManager->GetAlienArray()[i]->GetAlienState() == AlienEnum::Diving && !m_TheAlienManager->GetAlienArray()[i]->GetIsDead())
			{
				float radi0 =
					(m_ThePlayer->GetEntity()->GetWidth() +
						m_ThePlayer->GetEntity()->GetHeight()) * 0.25f;
				float radi1 =
					(m_TheAlienManager->GetAlienArray()[i]->GetEntity()->GetWidth() +
						m_TheAlienManager->GetAlienArray()[i]->GetEntity()->GetHeight()) * 0.25f;

				float dx = m_TheAlienManager->GetAlienArray()[i]->GetX() - m_ThePlayer->GetX();
				float dy = m_TheAlienManager->GetAlienArray()[i]->GetY() - m_ThePlayer->GetY();
				float distance = sqrt(dx * dx + dy * dy);

				if (distance < radi0 + radi1)
				{
					if (!m_ThePlayer->GetInvunerable() && !m_ThePlayer->GetIsDead())
					{
						m_ThePlayer->TakeDamage();
						m_TheAlienManager->GetAlienArray()[i]->AlienIsDead();
						break;
					}
				}
			}
		}
	}
	void Galaxians::MainMenuHandler(float dt)
	{
		if (m_CurrentGameState != GalaxiansGameEnum::GameActiveState)
		{
			if (Input::GetKey(44) || Input::GetKey(42))
			{
				Input::SetKey(44, false);
				Input::SetKey(42, false);
				m_TheUI->GalaxiansGameEnumState(&m_CurrentGameState);				
			}
		}
		if (m_ThePlayer->m_GAMEEND)
		{
			m_TheUI->GalaxiansGameEnumState(&m_CurrentGameState);
			m_TheAlienManager->ResetAliens(dt);
			m_ThePlayer->m_GAMEEND = false;
			m_ThePlayer->ResetToMaxHealth();
		}
		if (m_TheAlienManager->CheckIfAllAliensAreDead(dt))
		{
			m_TheUI->GalaxiansGameEnumState(&m_CurrentGameState);
			m_TheAlienManager->ResetAliens(dt);
			m_ThePlayer->m_GAMEEND = false;
		}
		
	}
}
