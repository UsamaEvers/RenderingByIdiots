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
		m_DeathSprite = new Sprite(new Surface("assets/explosionPlayer.png"), 4);
		SetX(a_Screen->GetWidth() * 0.5f - m_TheEntity->GetWidth() * 0.5f);
		SetY(a_Screen->GetHeight() - m_TheEntity->GetHeight() - 10.f);
		scXY[0] = a_Screen->GetWidth() * 0.5f - m_TheEntity->GetWidth() * 0.5f;
		scXY[1] = a_Screen->GetHeight() - m_TheEntity->GetHeight() - 10.f;

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
		scXY[0] = screen->GetWidth() * 0.5f - m_TheEntity->GetWidth() * 0.5f;
		scXY[1] = screen->GetHeight() - m_TheEntity->GetHeight() - 10.f;
		return true;
	}

	void GalaxianPlayer::Draw(Surface* screen)
	{
		if (!m_IsDead)
		{
			if (!m_IframesDrawing)
			{
				myMissile->Draw(screen);
				m_TheEntity->Draw(screen, GetX(), GetY());
			}
		}
		else
		{
			if (!m_DeathAnimationDone)
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
			UpdateIFrames(dt);
		}
		else
		{
			Respawn();
			DeathAnimationUpdate(dt);
		}
	}

	void GalaxianPlayer::TakeDamage()
	{
		if (!m_IsDead)
		{
			m_Health -= 1;
			m_IsDead = true;
			m_DeathAnimationDone = false;

			//Get the alive player sprite so that the difference in widht and height can be calculated.
			float standardSpriteWidth = m_TheEntity->GetWidth() * 0.5f;
			float standardSpriteheight = m_TheEntity->GetHeight() * 0.5f;

			SwitchSprite();
			float WidthDifference = m_TheEntity->GetWidth() * 0.5f - standardSpriteWidth;
			float HeightDifference = m_TheEntity->GetHeight() * 0.5f - standardSpriteheight;

			//remove the difference from the current position to set it correctly.
			SetX(GetX() - WidthDifference);
			SetY(GetY() - HeightDifference);
			myMissile->FollowPlayer(GetX() + (m_TheEntity->GetWidth() / 2), GetY() - 3);
			m_SecsBetweenFrames = 0.5f;
		}
	}

	void GalaxianPlayer::Respawn()
	{
		if (m_Health < 0)
		{
			m_GAMEEND = true;
			m_PlayerScore = 0;
		}
		else //Respawn the player
		{
			if (Input::GetKey(44))
			{
				//Checks if the animation is done and resets values for it being alive.
				if (m_DeathAnimationDone) {
					m_IsDead = false;
					m_Invunerable = true;
					m_InvunerableTime = 2.0f;
					m_IFramesTime = 0.2f;
					SetX(m_SpawnPos);
					SetY(scXY[1]);
					SwitchSprite();
				}
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

	void GalaxianPlayer::DeathAnimationUpdate(float dt)
	{
		if (!m_DeathAnimationDone && m_IsDead) {
			m_SecsBetweenFrames -= dt * 0.05f;
			if (m_SecsBetweenFrames < 0)
			{
				m_SecsBetweenFrames = 0.5f;
				switch (m_CurrentDeathAnimationFrame)
				{
				case 0:
					m_CurrentDeathAnimationFrame = 1;
					m_TheEntity->SetFrame(1);
					break;
				case 1:
					m_CurrentDeathAnimationFrame = 2;
					m_TheEntity->SetFrame(2);
					break;
				case 2:
					m_CurrentDeathAnimationFrame = 3;
					m_SecsBetweenFrames = 1.5f;
					m_TheEntity->SetFrame(3);
					break;
				case 3:
					m_DeathAnimationDone = true;
					m_CurrentDeathAnimationFrame = 0;
					m_TheEntity->SetFrame(0);
					break;
				default:
					break;
				}
			}
		}

	}

	void GalaxianPlayer::UpdateIFrames(float dt)
	{
		if (m_Invunerable) {
			if (m_InvunerableTime > 0)
			{
				m_InvunerableTime -= dt * 0.01f;
				m_IFramesTime -= dt * 0.01f;
			}
			else if (m_InvunerableTime < 0)
			{
				m_InvunerableTime = 2.0f;
				m_Invunerable = false;
				m_IframesDrawing = false;
			}
			if (m_IFramesTime < 0)
			{
				m_IFramesTime = 0.2f;
				if (m_IframesDrawing)
				{
					m_IframesDrawing = false;
				}
				else
					m_IframesDrawing = true;
			}
		}

	}

}