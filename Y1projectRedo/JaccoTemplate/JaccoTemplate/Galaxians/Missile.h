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
			m_AlienArray = a_AlienArray;
			m_fromPlayer = true;
		}
		Missile(GalaxianPlayer* a_Player)
		{
			m_Active = false;
			m_ThePlayer = a_Player;
			m_fromPlayer = false;
		}
		~Missile() {
			m_AlienArray = nullptr;
			delete m_AlienArray;
			m_ThePlayer = nullptr;
			delete m_ThePlayer;
		}

		/// Public Functions
		bool Init(Surface* screen) override;
		void Draw(Surface* screen) override;
		void Update(float dt, int& a_playerscore);

		void Shoot(int a_Xpos, int a_Ypos, bool a_ShootingUp);
		void FollowPlayer(float a_Xpos, float a_Ypos);

		/// Getters|Setters
		void SetIsFromPlayerTrue() { m_fromPlayer = true; }
		void SetActiveState(bool a_Val) { m_Active = a_Val; }
		bool getActiveState() { return m_Active; }

	private:
		/// Private Functions
		bool CheckForScreenCollision(float dt);
		bool CheckMissileAlienCollision(float dt, int& a_playerscore);
		bool CheckMissilePlayerCollision(float dt);

		/// Private Variables
		Alien** m_AlienArray;
		GalaxianPlayer* m_ThePlayer;
		float m_MaxYDistance = 0;
		//This should be -1, 0, 1
		float m_UpDowndirection = 0.f;
		bool m_Active;
		bool m_fromPlayer = false;
	};

}