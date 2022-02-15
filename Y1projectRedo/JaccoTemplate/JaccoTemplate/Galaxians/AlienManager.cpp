#include "AlienManager.h"
#include"../template/surface.h"
#include "../template/Entity.h"
#include "Alien.h"
#include "GalaxianPlayer.h"

#include <iostream>
namespace Tmpl8 {

	bool AlienManager::Init(Surface* a_Screen, GalaxianPlayer* a_Player, Entity* a_EntityArray[], int a_ArrayOffset)
	{
		int alienManagerArray[X][Y]
		{
			{0, 0, 0, 4, 0, 0, 4, 0, 0, 0},
			{0, 0, 3, 3, 3, 3, 3, 3, 0, 0},
			{0, 2, 2, 2, 2, 2, 2, 2, 2, 0},
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
		};
		m_HalfOfScreenWidth = a_Screen->GetWidth()*.5f;

		m_ThePlayer = a_Player;
		m_AlienArray = new Alien * [6 * 10];
		int xOffsetFromScreen = (int)(a_Screen->GetWidth() / 8);
		int yOffsetFromScreen = (int)(a_Screen->GetHeight() / 16);
		int yOffset = 15;
		int xOffset = 15;
		int OneOrZero = 0;
		for (int a_X = 0; a_X < Y; a_X++)
		{
			for (int a_Y = 0; a_Y < X; a_Y++)
			{

				switch (alienManagerArray[a_Y][a_X])
				{
				case 0:
					m_AlienArray[a_X * X + a_Y] = (new Alien())->Init(a_Screen,
						new Sprite(new Surface("assets/shooter.png"), 2),
						a_Player, GalaxianEnemyEnum::none,
						xOffsetFromScreen + xOffset * a_X,
						yOffsetFromScreen + yOffset * a_Y, 0, OneOrZero);
					m_AlienArray[a_X * X + a_Y]->AlienIsDead();
					m_AlienArray[a_X * X + a_Y]->SetPlayDeathAnimationToFalse();

					break;
				case 1:
					m_AlienArray[a_X * X + a_Y] = (new Alien())->Init(a_Screen,
						new Sprite(new Surface("assets/galaxianC.png"), 2),
						a_Player, GalaxianEnemyEnum::blue,
						xOffsetFromScreen + xOffset * a_X,
						yOffsetFromScreen + yOffset * a_Y, 60, OneOrZero);
					break;
				case 2:
					m_AlienArray[a_X * X + a_Y] = (new Alien())->Init(a_Screen,
						new Sprite(new Surface("assets/galaxianB.png"), 2),
						a_Player, GalaxianEnemyEnum::purple,
						xOffsetFromScreen + xOffset * a_X,
						yOffsetFromScreen + yOffset * a_Y, 80, OneOrZero);
					break;
				case 3:
					m_AlienArray[a_X * X + a_Y] = (new Alien())->Init(a_Screen,
						new Sprite(new Surface("assets/galaxianA.png"), 2),
						a_Player, GalaxianEnemyEnum::red,
						xOffsetFromScreen + xOffset * a_X,
						yOffsetFromScreen + yOffset * a_Y, 100, OneOrZero);
					break;
				case 4:
					m_AlienArray[a_X * X + a_Y] = (new Alien())->Init(a_Screen,
						new Sprite(new Surface("assets/elite.png"), 1),
						a_Player, GalaxianEnemyEnum::elite,
						xOffsetFromScreen + xOffset * a_X,
						yOffsetFromScreen + yOffset * a_Y, 200, OneOrZero);
					break;
				default:
					break;
				}
			}
			if (OneOrZero == 0)
				OneOrZero = 1;
			else
				OneOrZero = 0;
		}
		for (int i = 0; i < 60; i++)
		{
			a_EntityArray[i + a_ArrayOffset] = m_AlienArray[i];
		}
		return true;
	}

	void AlienManager::Update(Surface* a_Screen, float dt)
	{
		FormationMove(a_Screen, dt);
		StateChange(dt);
		ReturnToFormation();
		ResetFormation(dt);
	}

	void AlienManager::ResetAliens(float dt)
	{
		for (int i = 1; i < 60; i++)
		{
			m_AlienArray[i]->SetStateToReturn();
			m_AlienArray[i]->SetResetFormation(true);

		}
		
		ReturnToFormation();
		ResetFormation(dt);
		for (int i = 1; i < 60; i++)
		{
			m_AlienArray[i]->SetPositionAfterReset();
			if (m_AlienArray[i]->GetGalaxianEnemyState() != GalaxianEnemyEnum::none)
			{
				m_AlienArray[i]->AlienIsAlive();
				m_AlienArray[i]->UpdateState();
				m_AlienArray[i]->ResetAlien();

			}
		}
	}

	void AlienManager::FormationMove(Surface* a_Screen, float dt)
	{
		float width = a_Screen->GetWidth();

		if (m_LeftDirection) // check the furthest left first
		{
			int startmin = 0;
			int startmax = 6;
			bool repeat = false;
			int it = CheckRightColumn(startmin, startmax);
			if (0 < it && 60 > it)
				m_LeftDirection = false;
		}
		else
		{
			int startmin = 54;
			int startmax = 60;
			int it = CheckLeftColumn(startmin, startmax, width);
			if (0 < it && 60 > it)
				m_LeftDirection = true;
		}

		if (!m_LeftDirection)
		{
			for (int i = 0; i < 60; i++)
			{
				m_AlienArray[i]->SetDirectionToRight();
			}
		}
		else
		{
			for (int i = 0; i < 60; i++)
			{
				m_AlienArray[i]->SetDirectionToLeft();
			}
		}

	}

	void AlienManager::StateChange(float dt)
	{
		bool test = m_ThePlayer->GetInvunerable();
		if (!m_ThePlayer->GetIsDead() && !m_ThePlayer->GetInvunerable())
		{
			bool a = test;
			m_Timer -= dt;
			if (m_Timer < 0)
			{
				m_Timer = rand() % 10 * 20.f + 2.5f;
				//check which side of screen 
				int checkLeftSide = rand() % 2;
				if (checkLeftSide == 0)
				{
					int it = CheckRightColumnState(0, 6);
				}
				else
					int it = CheckLeftColumnState(54, 60);
			}
		}
	}

	void AlienManager::ResetFormation(float dt)
	{
		for (int i = 0; i < 60; i++)
		{
			if (m_AlienArray[i]->GetResetFormation())
			{
				m_AlienArray[i]->SetAnimationRemainderTime(m_AlienArray[0]->GetAnimationRemainderTime());
				unsigned int oneorzero = i / 6;
				int currentAnimationFrame = 0;
				int AlternativeValue = 1;
				if (m_AlienArray[0]->GetCurrentAnimationFrame() == 1)
				{
					currentAnimationFrame = 1;
					AlternativeValue = 0;
				}
				if (0==oneorzero|| 2 == oneorzero || 4 == oneorzero || 6 == oneorzero || 8 == oneorzero )
				{
					m_AlienArray[i]->SetCurrentAnimationFrame(currentAnimationFrame);
				}
				else if (1 == oneorzero || 3 == oneorzero || 5 == oneorzero || 7 == oneorzero || 9 == oneorzero)
				{
					m_AlienArray[i]->SetCurrentAnimationFrame(AlternativeValue);
				}
				m_AlienArray[i]->SetResetFormation(false);
			}
		}
	}

	void AlienManager::ReturnToFormation()
	{
		for (int i = 0; i < 60; i++)
		{
			if (m_AlienArray[i]->GetAlienState() == AlienEnum::Returning)
			{
				vec2 a = CalculateReturnPositions(i);
				m_AlienArray[i]->SetReturnPosition(a.x, a.y);
			}
		}
	}

	vec2 AlienManager::CalculateReturnPositions(int a_It)
	{
		int offset = 15;
		for (int a_X = 0; a_X < Y; a_X++)
		{
			for (int a_Y = 0; a_Y < X; a_Y++)
			{
				if (a_X * X + a_Y == a_It)
				{
					vec2 alienZeroOffset = vec2(m_AlienArray[0]->GetX(), m_AlienArray[0]->GetY());
					return alienZeroOffset + vec2(offset * a_X, offset * a_Y);
				}
			}
		}

	}

	int AlienManager::CheckRightColumn(int a_ItMin, int a_ItMax)
	{
		if (a_ItMin == 60)
			return -1;
		for (int i = a_ItMin; i < a_ItMax; i++)
		{
			if (!m_AlienArray[i]->GetIsDead())
			{
				if (m_AlienArray[i]->GetAlienState() == AlienEnum::Formation && m_AlienArray[i]->GetX() < 10)
				{
					return i;
				}
			}
		}
		CheckRightColumn(a_ItMin + 6, a_ItMax + 6);
	}

	int AlienManager::CheckLeftColumn(int a_ItMin, int a_ItMax, int a_Width)
	{
		if (a_ItMax == 0)
			return -1;

		for (int i = a_ItMin; i < a_ItMax; i++)
		{
			if (!m_AlienArray[i]->GetIsDead())
			{
				if (m_AlienArray[i]->GetAlienState() == AlienEnum::Formation && m_AlienArray[i]->GetX() > a_Width - 10 - m_AlienArray[i]->GetEntity()->GetWidth())
				{
					return i;
				}
			}
		}
		CheckLeftColumn(a_ItMin - 6, a_ItMax - 6, a_Width);
	}

	int AlienManager::CheckRightColumnState(int a_ItMin, int a_ItMax)
	{
		if (a_ItMin == 60)
			return -1;
		for (int i = a_ItMin; i < a_ItMax; i++)
		{
			if (!m_AlienArray[i]->GetIsDead())
			{
				if (m_AlienArray[i]->GetAlienState() == Tmpl8::AlienEnum::Formation)
				{
					m_AlienArray[i]->UpdateState();
					if (m_AlienArray[i]->GetX() > m_HalfOfScreenWidth)
					{
						m_AlienArray[i]->SetArcLeftTrue(false);
						m_AlienArray[i]->SetArcPivot(false);
					}
					else
					{
						m_AlienArray[i]->SetArcLeftTrue(true);
						m_AlienArray[i]->SetArcPivot(true);
					}
					m_AlienArray[i]->SetDivePosition(m_ThePlayer->GetX(), m_ThePlayer->GetY());
					return	i;
				}
			}
		}

		CheckRightColumnState(a_ItMin + 6, a_ItMax + 6);
	}

	int AlienManager::CheckLeftColumnState(int a_ItMin, int a_ItMax)
	{
		if (a_ItMax == 0)
			return -1;
		for (int i = a_ItMin; i < a_ItMax; i++)
		{
			if (!m_AlienArray[i]->GetIsDead())
			{
				if (m_AlienArray[i]->GetAlienState() == Tmpl8::AlienEnum::Formation)
				{
					m_AlienArray[i]->UpdateState();
					if (m_AlienArray[i]->GetX()>m_HalfOfScreenWidth)
					{
						m_AlienArray[i]->SetArcLeftTrue(false);
						m_AlienArray[i]->SetArcPivot(false);
					}
					else
					{
						m_AlienArray[i]->SetArcLeftTrue(true);
						m_AlienArray[i]->SetArcPivot(true);
					}
					m_AlienArray[i]->SetDivePosition(m_ThePlayer->GetX(), m_ThePlayer->GetY() + m_ThePlayer->GetEntity()->GetHeight());
					return	i;
				}
			}
		}
		CheckLeftColumnState(a_ItMin - 6, a_ItMax - 6);
	}
}