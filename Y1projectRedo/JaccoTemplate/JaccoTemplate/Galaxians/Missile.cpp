#include "Missile.h"
#include "../template/surface.h"
#include "Alien.h"
#include "GalaxianPlayer.h"
namespace Tmpl8
{
	bool Missile::Init(Surface* screen)
	{
		theEntity = new Sprite(new Surface("assets/verticalline.png"), 1);
		m_MaxYDistance = screen->GetHeight();

		return true;
	}

	void Missile::Draw(Surface* screen)
	{
		//Player's missile is always drawn, while the aliens' isn't
		if (m_fromPlayer)
		{
			theEntity->Draw(screen, GetX(), GetY());
		}
		else if (m_Active)
		{
			theEntity->Draw(screen, GetX(), GetY());
		}

	}

	void Missile::Update(float dt, int& a_playerscore)
	{
		if (m_Active)
		{
			float speed = 1.5f * dt;
			if (direction > 0.1f)		// shooting up
			{
				SetY(GetY() - speed);
			}
			else if (direction < -0.1f)	// shooting down
			{
				SetY(GetY() + speed);
			}
			//Check if missile is from the player
			if (m_fromPlayer)
			{
				CheckMissileAlienCollision(dt, a_playerscore);
			}
			else
			{
				CheckMissilePlayerCollision(dt);
			}
			CheckForScreenCollision(dt);	
		}
		
	}

	void Missile::Shoot(int a_Xpos, int a_Ypos, bool a_ShootingUp)
	{
		m_Active = true;
		SetX(a_Xpos);
		SetY(a_Ypos);
		if (a_ShootingUp)
			direction = 1.f;
		else
			direction = -1.f;
	}

	void Missile::FollowPlayer(float a_Xpos, float a_Ypos)
	{
		SetX(a_Xpos);
		SetY(a_Ypos);
	}

	bool Missile::CheckForScreenCollision(float dt)
	{
		if (GetY() > m_MaxYDistance)
		{
			m_Active = false;
			direction = 0.f;
		}
		else if (GetY() < 10)
		{
			m_Active = false;
			direction = 0.f;
		}
		return true;
	}

	bool Missile::CheckMissileAlienCollision(float dt, int& a_playerscore)
	{
		//get dimensions of missile
		float mw = GetEntity()->GetWidth();
		float mh = GetEntity()->GetHeight();
		float mx = GetX();
		float my = GetY();
		float radi1 = (mw + mh) * 0.5f;
		//loop over all aliens
		for (int i = 0; i < 60; i++)
		{
			//don't check dead aliens
			if (!m_AlienArray[i]->GetIsDead())
			{
				//get dimensions of aliens
				float pw = m_AlienArray[i]->GetEntity()->GetWidth();
				float ph = m_AlienArray[i]->GetEntity()->GetHeight();
				float px = m_AlienArray[i]->GetX();
				float py = m_AlienArray[i]->GetY();
				float radi0 = (pw + ph) * 0.25f;

				//get dimensions for distance
				float dx = mx - px;
				float dy = my - py;
				float distance = sqrt(dx * dx + dy * dy);

				//check for collision
				if (distance < radi0 + radi1)
				{
					//deactivate alien and missile.
					m_Active = false;
					m_AlienArray[i]->AlienIsDead(); 
					a_playerscore += m_AlienArray[i]->GetScoreGivenOnDeath();
				}
			}
		}
		return true;
	}
	bool Missile::CheckMissilePlayerCollision(float dt)
	{
		float pw = thePlayer->GetEntity()->GetWidth();
		float ph = thePlayer->GetEntity()->GetHeight();
		float px = thePlayer->GetX();
		float py = thePlayer->GetY();
		float radi0 = (pw + ph) * 0.25f;

		float mw = GetEntity()->GetWidth();
		float mh = GetEntity()->GetHeight();
		float mx = GetX();
		float my = GetY();
		float radi1 = (mw + mh) * 0.5f;

		float dx = mx - px;
		float dy = my - py;
		float distance = sqrt(dx * dx + dy * dy);

		if (distance < radi0 + radi1)
		{
			m_Active = false;
			//This needs to kill the player.
			if (!thePlayer->GetInvunerable() && !thePlayer->GetIsDead())
			{
				thePlayer->TakeDamage();
			}
		}
		return true;
	}
}