#include "Alien.h"
#include "../template/surface.h"
#include <math.h>       /* sin */
#define PI 3.14159265
#define degreetorad(deg) ((deg)*(PI/180))
namespace Tmpl8 {
	Alien::Alien()
	{

	}
	Alien* Alien::Init(Surface* screen, Sprite* a_AlienType, GalaxianPlayer* a_GalaxianPlayer, GalaxianEnemyEnum a_Galaxiansenemytype, int a_Xpos, int a_Ypos, int a_DeathScore, int a_StartingAnimationFrame)
	{
		m_ScoreGivenOnDeath = a_DeathScore;
		m_CurrentAnimationFrame = a_StartingAnimationFrame;
		m_TheEntity = a_AlienType;
		m_DeathSprite = new Sprite(new Surface("assets/explosionAlien.jpg"), 4);

		SetX(a_Xpos);
		SetY(a_Ypos);
		m_CurrentAlienState = AlienEnum::Formation;
		m_MyGalaxianEnemyState = a_Galaxiansenemytype;
		for (int i = 0; i < MISSILEAMOUNT; i++)
		{
			m_MissileArray[i] = new Missile(a_GalaxianPlayer);
			m_MissileArray[i]->Init(screen);
		}
		return this;
	}

	void Alien::Update(float dt)
	{
		if (m_IsDead)
		{
			if(!m_PlayBombAnimation)
				Move(dt);
			DeathAnimationUpdate(dt);
			//	UpdateAnimation(dt);
		}
		else {
			switch (m_CurrentAlienState)
			{
			case Tmpl8::AlienEnum::Formation:
				Move(dt);
				UpdateAnimation(dt);
				break;
			case Tmpl8::AlienEnum::Arcing:
				Arc(true, dt);
				break;
			case Tmpl8::AlienEnum::Diving:
				Dive(dt);
				Shoot(0, 0, dt);
				for (int i = 0; i < MISSILEAMOUNT; i++)
				{
					int thisvalueisonlyusedfortheplayer = 0;
					m_MissileArray[i]->Update(dt, thisvalueisonlyusedfortheplayer);
				}
				break;
			case Tmpl8::AlienEnum::Returning:
				Return(dt);
				break;
			default:
				break;
			}
		}
	}

	void Alien::Draw(Surface* screen)
	{
		if (!m_IsDead)
		{
			m_TheEntity->Draw(screen, GetX(), GetY());

			for (int i = 0; i < MISSILEAMOUNT; i++)
			{
				m_MissileArray[i]->Draw(screen);
			}
		}
		else if (m_ExplosionAnimationPlaying)
		{
			m_TheEntity->Draw(screen, GetX(), GetY());
		}
	}



	void Alien::UpdateAnimation(float dt)
	{
		if (m_TheEntity->Frames() > 1)
		{
			m_SecsBetweenFrames -= dt * 0.01f;
			if (m_SecsBetweenFrames < 0)
			{
				m_SecsBetweenFrames = 0.5f;
				switch (m_CurrentAnimationFrame)
				{
				case 0:
					m_CurrentAnimationFrame = 1;
					m_TheEntity->SetFrame(1);
					break;
				case 1:
					m_CurrentAnimationFrame = 0;
					m_TheEntity->SetFrame(0);
					break;
				default:
					break;
				}
			}
		}
	}

	void Alien::Move(float dt)
	{
		float movementOffset = 0.3f;
		if (m_MoveLeft)
			SetX(GetX() - movementOffset * dt);
		else
			SetX(GetX() + movementOffset * dt);
	}

	void Alien::Arc(bool arcLeft, float dt)
	{

		if (m_ArcLeft)	// move Left
		{
			float angleDirection = -5;
			float AngleForArc = degreetorad(angleDirection * m_FramesForArcing);
			SetX(cos(AngleForArc) * m_RadiusOfCircle + m_ArcPivot.x);
			SetY(sin(AngleForArc) * m_RadiusOfCircle + m_ArcPivot.y);
			m_FramesForArcing++;
		}
		else			// move Right
		{
			float angleDirection = 5;
			float AngleForArc = degreetorad(angleDirection * m_FramesForArcing + 180);
			SetX(cos(AngleForArc) * m_RadiusOfCircle + m_ArcPivot.x);
			SetY(sin(AngleForArc) * m_RadiusOfCircle + m_ArcPivot.y);
			m_FramesForArcing++;
		}
		if (m_FramesForArcing > 40)
		{
			m_FramesForArcing = 0;
			m_startPosition.x = GetX();
			m_startPosition.y = GetY();
			m_CurrentAlienState = AlienEnum::Diving;
		}
	}

	void Alien::Dive(float dt)
	{

		if (GetY() > m_endPosition.y * 1.5f)
		{
			UpdateState();
			m_DiveTime = 0;
			m_startPosition.x = GetX();
			SetY(-GetEntity()->GetHeight());
			m_startPosition.y = GetY();
		}
		else
		{
			m_DiveTime += dt * 0.005f;
			float xOffset = 10;
			SetX(lerp(m_startPosition.x, m_endPosition.x, m_DiveTime));
			SetY(lerp(m_startPosition.y, m_endPosition.y, m_DiveTime));
		}
	}

	void Alien::Shoot(int a_Xpos, int a_Ypos, float dt)
	{
		if (0 > m_ShootCooldown)
		{
			m_ShootCooldown = SHOOTCOOLDOWN;
			for (int i = 0; i < MISSILEAMOUNT; i++)
			{
				if (false == m_MissileArray[i]->getActiveState())
				{
					m_MissileArray[i]->Shoot(this->GetX(), this->GetY(), false);
					break;
				}
			}
		}
		else
		{
			m_ShootCooldown -= dt * 0.01f;
		}
	}

	void Alien::Return(float dt)
	{
		if (m_DiveTime > 1)
		{
			m_DiveTime = 0;
			UpdateState();
			m_ResetFormation = true;

			SetX(m_endPosition.x);
			SetY(m_endPosition.y);
		}
		else
		{
			m_DiveTime += dt * 0.005f;
			SetX(lerp(m_startPosition.x, m_endPosition.x, m_DiveTime));
			SetY(lerp(m_startPosition.y, m_endPosition.y, m_DiveTime));
		}
	}

	void Alien::DeathAnimationUpdate(float dt)
	{
		//Animation update for the alien's death animation
		//================================================
		if (m_PlayBombAnimation)
		{
			if (!m_ExplosionAnimationPlaying) {
				m_ExplosionAnimationPlaying = true;
				SwitchSprite();
				m_SecsBetweenFramesDeath = 0.5f;
			}
			if (m_ExplosionAnimationPlaying) {
				m_SecsBetweenFramesDeath -= dt * 0.0675f;
				if (m_SecsBetweenFramesDeath < 0)
				{
					m_SecsBetweenFramesDeath = 0.5f;
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
						m_SecsBetweenFramesDeath = 1.5f;
						m_TheEntity->SetFrame(3);
						break;
					case 3:
						m_ExplosionAnimationPlaying = false;
						m_PlayBombAnimation = false;
						SwitchSprite();
						break;
					default:
						break;
					}
				}
			}
		}
		
		//Animation update for the alien's normal animation
		//=================================================
		m_SecsBetweenFrames -= dt * 0.01f;
		if (m_SecsBetweenFrames < 0)
		{
			m_SecsBetweenFrames = 0.5f;
			switch (m_CurrentAnimationFrame)
			{
			case 0:
				m_CurrentAnimationFrame = 1;
				//m_TheEntity->SetFrame(1);
				break;
			case 1:
				m_CurrentAnimationFrame = 0;
			//	m_TheEntity->SetFrame(0);
				break;
			default:
				break;
			}
		}
	}




	float Alien::lerp(float a, float b, float f)
	{
		return a + f * (b - a);
	}

	void Alien::UpdateState()
	{
		switch (m_CurrentAlienState)
		{
		case Tmpl8::AlienEnum::Formation:
			m_CurrentAlienState = Tmpl8::AlienEnum::Arcing;
			break;
		case Tmpl8::AlienEnum::Arcing:
			m_CurrentAlienState = Tmpl8::AlienEnum::Diving;
			break;
		case Tmpl8::AlienEnum::Diving:
			m_CurrentAlienState = Tmpl8::AlienEnum::Returning;
			break;
		case Tmpl8::AlienEnum::Returning:
			m_CurrentAlienState = Tmpl8::AlienEnum::Formation;
			break;
		default:
			break;
		}
	}

	void Alien::SetDivePosition(float ax, float ay)
	{

		m_endPosition.x = ax;
		m_endPosition.y = ay;

	}

	void Alien::SetReturnPosition(float axpos, float aypos)
	{
		m_endPosition.x = axpos;
		m_endPosition.y = aypos;
	}

	void Alien::AlienIsDead()
	{
		m_IsDead = true;
		m_PlayBombAnimation = true;
		for (int i = 0; i < MISSILEAMOUNT; i++)
		{
			m_MissileArray[i]->SetActiveState(false);
		}
	}

	void Alien::AlienIsAlive()
	{
		m_IsDead = false;
	}

	void Alien::ResetAlien()
	{
		m_startPosition = vec2(0);
		m_endPosition = vec2(0);
		m_DiveTime = 0;
		m_PlayBombAnimation = false;
		m_ExplosionAnimationPlaying = false;
		for (int i = 0; i < MISSILEAMOUNT; i++)
		{
			m_MissileArray[i]->SetActiveState(false);
		}
	}

}