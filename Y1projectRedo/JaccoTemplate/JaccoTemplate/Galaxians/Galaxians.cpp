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

	bool draw = true;


	bool Galaxians::Init(Surface* screen)
	{
		//Init alienmanager
		theAlienManager = new AlienManager();
		Theplayer = new GalaxianPlayer(screen);
		theAlienManager->Init(screen, Theplayer, allEntities, 1);

		//init Player and Missile
		Missile* themissile = new Missile(theAlienManager->GetAlienArray());
		Theplayer->Init(screen, themissile);
		allEntities[0] = Theplayer;
		TheUI = new GalaxianUI();
		background = new Background(screen);
		TheUI->Init(screen,Theplayer->GetHealth());
		return true;
	}
	bool Galaxians::Update(Surface* screen, float dt)
	{
		MainMenuHandler(dt);
		CheckAlienPlayerCollision();
		background->Update(screen, dt);
		TheUI->Update(m_CurrentGameState, dt,Theplayer->GetPlayerScore());
		TheUI->UpdatePlayerHealth(Theplayer->GetHealth());

		if (GalaxiansGameEnum::GameActiveState == m_CurrentGameState)
		{
			theAlienManager->Update(screen, dt);
			for (int i = 0; i < 61; i++)
			{
				if (nullptr == allEntities[i])
					break;
				allEntities[i]->Update(dt);
			}
			return true;
		}
		
	}
	bool Galaxians::Draw(Surface* screen)
	{
		if (draw)
			TheUI->Draw(screen);
		background->Draw(screen);

		if (GalaxiansGameEnum::GameActiveState == m_CurrentGameState)
		{
			for (int i = 0; i < 61; i++)
			{
				if (nullptr == allEntities[i])
					break;
				allEntities[i]->Draw(screen);
			}
			return true;
		}
	}

	void Galaxians::CheckAlienPlayerCollision()
	{
		for (int i = 0; i < 60; i++)
		{
			float radi0 =
				(Theplayer->GetEntity()->GetWidth() +
					Theplayer->GetEntity()->GetHeight()) * 0.25f;
			float radi1 =
				(theAlienManager->GetAlienArray()[i]->GetEntity()->GetWidth() +
					theAlienManager->GetAlienArray()[i]->GetEntity()->GetHeight()) * 0.25f;

			float dx = theAlienManager->GetAlienArray()[i]->GetX() - Theplayer->GetX();
			float dy = theAlienManager->GetAlienArray()[i]->GetY() - Theplayer->GetY();
			float distance = sqrt(dx * dx + dy * dy);

			if (distance < radi0 + radi1)
			{
				if (!Theplayer->GetInvunerable() && !Theplayer->GetIsDead())
				{
 					Theplayer->TakeDamage();
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
				TheUI->GalaxiansGameEnumState(&m_CurrentGameState);
			
				
			}
		}
		if (Theplayer->m_GAMEEND)
		{
			TheUI->GalaxiansGameEnumState(&m_CurrentGameState);
			theAlienManager->ResetAliens(dt);
			Theplayer->m_GAMEEND = false;
			Theplayer->SetHealth();
		}
	
	}
}
