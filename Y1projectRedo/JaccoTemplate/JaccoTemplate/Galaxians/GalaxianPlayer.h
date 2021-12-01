#pragma once
#include "../template/Entity.h"
namespace Tmpl8 {
	class Sprite;
	class Missile;
	class GalaxianPlayer: public Entity //too much inheritance is overdone		//start at 1100 stop 1352
	{
	public:
		GalaxianPlayer();
		GalaxianPlayer(Surface* a_Screen);
		~GalaxianPlayer();
		bool Init(Surface* screen) override { return true; }
		bool Init(Surface* screen, Missile* a_entity);
		void Draw(Surface* screen)  override;
		void Update(float dt) override;
		void changepostotestcoll() { SetY(50); }
		void TakeDamage();
		void Respawn();
		bool GetIsDead() { return m_IsDead; }
		int GetPlayerScore() { return m_PlayerScore; }
		int GetHealth() { return m_Health; }
		void SetHealth() {  m_Health = 3; }
		bool GetInvunerable() { return m_Invunerable; }
		bool m_GAMEEND = false;
	private:
		Missile* myMissile;

		void Move(float dt);
		void Shoot(float dt);
		int SpawnPos = 0;
		int m_Health=0;
		int frame = 0;
		int frame0 = 0;
		int m_PlayerScore = 0;
		float furthestLeft=0.f;
		float furthestRight=0.f;
		bool m_IsDead = false;
		bool m_Invunerable = false;
		float m_InvunerableTime = 2.f;
	};
}

