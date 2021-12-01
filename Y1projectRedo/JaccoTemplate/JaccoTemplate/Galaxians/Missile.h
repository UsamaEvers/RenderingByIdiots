#pragma once
#include "../template/Entity.h"

namespace Tmpl8
{
	class Alien;
	class GalaxianPlayer;
	class Missile :public Entity
	{
	public:
		Missile() { m_Active = false; }
		Missile(Alien** a_AlienArray) 
		{ 
			m_Active = false;
			//m_AlienArray = new Alien * [6 * 10];
			m_AlienArray = a_AlienArray;
			m_fromPlayer = true;
		}
		Missile(GalaxianPlayer* a_Player)
		{
			m_Active = false;
			thePlayer = a_Player;
			m_fromPlayer = false;
		}
		~Missile() {
			m_AlienArray = nullptr;
			delete m_AlienArray;
			thePlayer = nullptr;
			delete thePlayer;
		}
		void Draw(Surface* screen) override;
		bool Init(Surface* screen) override;
		void Shoot(int a_Xpos, int a_Ypos, bool a_ShootingUp);
		void FollowPlayer(float a_Xpos, float a_Ypos);
		void Update(float dt,  int& a_playerscore) ;
		void SetIsFromPlayerTrue() { m_fromPlayer = true; }
		bool getActiveState() { return m_Active; }
		void SetActiveState(bool a_Val) { m_Active = a_Val; }
	private:
		bool CheckForScreenCollision(float dt);
		bool CheckMissileAlienCollision(float dt, int& a_playerscore);
		bool CheckMissilePlayerCollision(float dt);
		Alien** m_AlienArray;
		GalaxianPlayer* thePlayer;
		float m_MaxYDistance = 0;
		float direction = 0.f;
		bool m_Active;
		bool m_fromPlayer = false;
	};

}