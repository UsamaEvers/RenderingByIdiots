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
		theEntity = a_AlienType;
		SetX(a_Xpos);
		SetY(a_Ypos);
		myState = AlienStates::Formation;
		m_MyGalaxianEnemyState = a_Galaxiansenemytype;
		for (int i = 0; i < MISSILEAMOUNT; i++)
		{
			missiles[i] = new Missile(a_GalaxianPlayer);
			missiles[i]->Init(screen);
		}
		return this;
	}

	void Alien::Update(float dt)
	{
		if (m_IsDead)
		{
			Move(dt);
			UpdateAnimation(dt);
		}
		else {
			switch (myState)
			{
			case Tmpl8::AlienStates::Formation:
				Move(dt);
				UpdateAnimation(dt);
				break;
			case Tmpl8::AlienStates::Arcing:
				Arc(true, dt);
				break;
			case Tmpl8::AlienStates::Diving:
				Dive(dt);
				Shoot(0, 0, dt);
				for (int i = 0; i < MISSILEAMOUNT; i++)
				{
					int thisvalueisonlyusedfortheplayer = 0;
					missiles[i]->Update(dt, thisvalueisonlyusedfortheplayer);
				}
				break;
			case Tmpl8::AlienStates::Returning:
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
			theEntity->Draw(screen, GetX(), GetY());

			for (int i = 0; i < MISSILEAMOUNT; i++)
			{
				missiles[i]->Draw(screen);
			}
		}
	}



	void Alien::UpdateAnimation(float dt)
	{
		if (theEntity->Frames() > 1)
		{
			m_SecsBetweenFrames -= dt * 0.01f;
			if (m_SecsBetweenFrames < 0)
			{
				m_SecsBetweenFrames = 0.5f;
				switch (m_CurrentAnimationFrame)
				{
				case 0:
					m_CurrentAnimationFrame = 1;
					theEntity->SetFrame(1);
					break;
				case 1:
					m_CurrentAnimationFrame = 0;
					theEntity->SetFrame(0);
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
			float AngleForArc = degreetorad(angleDirection * frame);
			SetX(cos(AngleForArc) * m_RadiusOfCircle + m_ArcPivot.x);
			SetY(sin(AngleForArc) * m_RadiusOfCircle + m_ArcPivot.y);
			frame++;
		}
		else			// move Right
		{
			float angleDirection = 5;
			float AngleForArc = degreetorad(angleDirection * frame + 180);
			SetX(cos(AngleForArc) * m_RadiusOfCircle + m_ArcPivot.x);
			SetY(sin(AngleForArc) * m_RadiusOfCircle + m_ArcPivot.y);
			frame++;
		}
		if (frame > 40)
		{
			frame = 0;
			m_startPosition.x = GetX();
			m_startPosition.y = GetY();
			myState = AlienStates::Diving;
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


			//	m_ThePlayerVar.
					//SetX(GODSWORDS(divePositionX, diveToPositionX * 0.7f, diveToPositionX +xOffset, diveToPositionX*0.8f, dt));
					//SetY(GODSWORDS(divePositionY, diveToPositionY * 0.5f, diveToPositionY * 1.0f, diveToPositionY*1.1, dt));
		}
	}

	void Alien::Shoot(int a_Xpos, int a_Ypos, float dt)
	{
		if (0 > m_ShootCooldown)
		{
			m_ShootCooldown = SHOOTCOOLDOWN;
			for (int i = 0; i < MISSILEAMOUNT; i++)
			{
				if (false == missiles[i]->getActiveState())
				{
					missiles[i]->Shoot(this->GetX(), this->GetY(), false);
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
			// write code here
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

	float Alien::GODSWORDS(float a_Val0, float a_Val1, float a_Val2, float a_Val3, float a_dt)
	{
		m_DiveTime += a_dt * 0.001f;
		return ((1 - m_DiveTime) * (1 - m_DiveTime) * (1 - m_DiveTime) * a_Val0 + 3 * m_DiveTime * (1 - m_DiveTime) * (1 - m_DiveTime) * a_Val1 + 3 * (1 - m_DiveTime) * m_DiveTime * m_DiveTime * a_Val2 + m_DiveTime * m_DiveTime * m_DiveTime * a_Val3);
	}

	float Alien::lerp(float a, float b, float f)
	{
		return a + f * (b - a);
	}

	void Alien::UpdateState()
	{
		switch (myState)
		{
		case Tmpl8::AlienStates::Formation:
			myState = Tmpl8::AlienStates::Arcing;
			break;
		case Tmpl8::AlienStates::Arcing:
			myState = Tmpl8::AlienStates::Diving;
			break;
		case Tmpl8::AlienStates::Diving:
			myState = Tmpl8::AlienStates::Returning;
			break;
		case Tmpl8::AlienStates::Returning:
			myState = Tmpl8::AlienStates::Formation;
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

		for (int i = 0; i < MISSILEAMOUNT; i++)
		{
			missiles[i]->SetActiveState(false);
		}
	}
	void Alien::SetResettPosition()
	{
		m_startPosition = vec2(0);
		m_endPosition = vec2(0);
		m_DiveTime = 0;
		for (int i = 0; i < MISSILEAMOUNT; i++)
		{
			missiles[i]->SetActiveState(false);
		}

	}

}