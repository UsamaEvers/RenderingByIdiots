#include "GalaxianPlayer.h"
#include "../template/surface.h"
#include "../template/Input.h"
#include "Missile.h"
#include <math.h>       /* sin */
#define PI 3.14159265
#define degreetorad(deg) (deg*PI/180)
namespace Tmpl8 {
	GalaxianPlayer::GalaxianPlayer()
	{
		theEntity = new Sprite(new Surface("assets/shooter.png"), 1);

	}
	GalaxianPlayer::GalaxianPlayer(Surface* a_Screen)
	{
		theEntity = new Sprite(new Surface("assets/shooter.png"), 1);
		SetX(a_Screen->GetWidth() * 0.5f - theEntity->GetWidth() * 0.5f);
		SetY(a_Screen->GetHeight() - theEntity->GetHeight() - 10.f);
	}
	GalaxianPlayer::~GalaxianPlayer()
	{
		delete theEntity;
	}

	bool GalaxianPlayer::Init(Surface* screen, Missile* a_entity)
	{
		furthestRight = screen->GetWidth();
		furthestLeft = 5;
		m_Health = 3;
		SetX(screen->GetWidth() * 0.5f - theEntity->GetWidth() * 0.5f);
		SpawnPos = screen->GetWidth() * 0.5f - theEntity->GetWidth() * 0.5f;
		SetY(screen->GetHeight() - theEntity->GetHeight() - 10.f);
		myMissile = a_entity;
		myMissile->SetIsFromPlayerTrue();
		myMissile->Init(screen);
		return true;
	}

	void GalaxianPlayer::Draw(Surface* screen)
	{
		if (!m_IsDead)
		{
			myMissile->Draw(screen);
			theEntity->Draw(screen, GetX(), GetY());
		}
	}

	void GalaxianPlayer::Update(float dt)
	{
		if (!m_IsDead)
		{
			myMissile->Update(dt, m_PlayerScore);
			Move(dt);
			Shoot(dt);
			if (m_InvunerableTime > 0)
			{
 				m_InvunerableTime -= dt * 0.01f;
			}
			else if (m_InvunerableTime < 0)
			{
				m_InvunerableTime = 2.0f;
				m_Invunerable = false;
			}
		}
		else
			Respawn();
	}

	void GalaxianPlayer::TakeDamage()
	{
		if (!m_IsDead)
		{
			m_Health -= 1;
			m_IsDead = true;
		}
	}

	void GalaxianPlayer::Respawn()
	{
		if (m_Health < 0)
		{
			m_GAMEEND = true;
			m_PlayerScore = 0;
		}
		else // continue
		{
			if (Input::GetKey(44))
			{
				m_IsDead = false;
				SetX(SpawnPos);
				m_Invunerable = true;
			}
		}
	}

	void GalaxianPlayer::Move(float dt)
	{
		float distanceTraveled = 0.5f * dt;
		if (Input::GetKey(80))
		{
			if (GetX() > furthestLeft)
				SetX(GetX() - distanceTraveled);
		}
		if (Input::GetKey(79))
		{
			if (GetX() + theEntity->GetWidth() + distanceTraveled < furthestRight)
				SetX(GetX() + distanceTraveled);
		}
	}

	void GalaxianPlayer::Shoot(float dt)
	{
		float Xpos = GetX() + (theEntity->GetWidth() / 2);
		if (Input::GetKey(44) && !myMissile->getActiveState())
		{
			myMissile->Shoot(Xpos, GetY(), true);
			Input::SetKey(44, false);
		}
		else if (!myMissile->getActiveState())
		{
			myMissile->FollowPlayer(Xpos, GetY() - 3);
		}
		float arcAngle = 5;
		if (Input::GetKey(40) /*&& frame < 40*/)
		{
			//SetY(GetY() +  dt);
			//float angleDirection = -10;
			//float radiusForArc = degreetorad(angleDirection *frame);
			//SetX(cos(radiusForArc) * arcAngle + GetX());
			//SetY(sin(radiusForArc) * arcAngle + GetY());		
			//frame++;
		}
		if (Input::GetKey(42) && frame0 < 40)
		{
			
		}

	}

}