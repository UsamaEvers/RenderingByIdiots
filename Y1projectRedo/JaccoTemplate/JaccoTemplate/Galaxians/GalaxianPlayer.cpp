#include "GalaxianPlayer.h"
#include "../template/surface.h"
#include "../template/Input.h"
#include "Missile.h"
#include <math.h>       /* sin */
#define PI 3.14159265
#define degreetorad(deg) (deg*PI/180)
namespace Tmpl8 {

	GalaxianPlayer::GalaxianPlayer(Surface* a_Screen)
	{
		m_TheEntity = new Sprite(new Surface("assets/shooter.png"), 1);
		SetX(a_Screen->GetWidth() * 0.5f - m_TheEntity->GetWidth() * 0.5f);
		SetY(a_Screen->GetHeight() - m_TheEntity->GetHeight() - 10.f);
	}
	GalaxianPlayer::~GalaxianPlayer()
	{
		myMissile = nullptr;
		delete myMissile;
	}

	bool GalaxianPlayer::Init(Surface* screen, Missile* a_entity)
	{
		m_FurthestRight = screen->GetWidth();
		m_FurthestLeft = 5;
		m_Health = 3;
		SetX(screen->GetWidth() * 0.5f - m_TheEntity->GetWidth() * 0.5f);
		m_SpawnPos = screen->GetWidth() * 0.5f - m_TheEntity->GetWidth() * 0.5f;
		SetY(screen->GetHeight() - m_TheEntity->GetHeight() - 10.f);
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
			m_TheEntity->Draw(screen, GetX(), GetY());
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
				SetX(m_SpawnPos);
				m_Invunerable = true;
			}
		}
	}

	void GalaxianPlayer::Move(float dt)
	{
		float distanceTraveled = 0.5f * dt;
		if (Input::GetKey(80))
		{
			if (GetX() > m_FurthestLeft)
				SetX(GetX() - distanceTraveled);
		}
		if (Input::GetKey(79))
		{
			if (GetX() + m_TheEntity->GetWidth() + distanceTraveled < m_FurthestRight)
				SetX(GetX() + distanceTraveled);
		}
	}

	void GalaxianPlayer::Shoot(float dt)
	{
		float Xpos = GetX() + (m_TheEntity->GetWidth() / 2);
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
	

	}

}