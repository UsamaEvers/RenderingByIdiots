#pragma once
#include "../template/Entity.h"
#include "../template/template.h"
#include "Missile.h"
namespace Tmpl8 {
	class Surface;
	class GalaxianPlayer;
	enum class AlienEnum
	{
		Formation = 0,
		Arcing,
		Diving,
		Returning,
	};
	enum class GalaxianEnemyEnum
	{
		none = 0,
		blue,
		red,
		purple,
		elite
	};
	class Alien : public Entity
	{
	public:

		Alien();
		~Alien() {}
		Alien* Init(Surface* screen, Sprite* a_AlienType, GalaxianPlayer* a_GalaxianPlayer, GalaxianEnemyEnum galaxiansenemytype,int a_Xpos, int a_Ypos, int a_DeathScore, int StartingAnimationFrame);
		void Update(float dt);
		void Draw(Surface* screen);
		
		/// Updates
		void UpdateState();		
		void SetDivePosition(float ax, float ay);
		void SetReturnPosition(float axpos, float aypos);
		void AlienIsDead(); 
		void AlienIsAlive();
		void ResetAlien();


		/// All the setters		
		void SetPositionAfterReset()						{ SetX(m_endPosition.x); SetY(m_endPosition.y);}
		void SetStateToReturn()								{ m_CurrentAlienState = AlienEnum::Returning; }
		void SetDirectionToLeft()							{ m_MoveLeft = true; }
		void SetDirectionToRight()							{ m_MoveLeft = false; }
		void SetAnimationRemainderTime(float a_val)			{ m_SecsBetweenFrames = a_val; }
		void SetCurrentAnimationFrame(unsigned int a_Val)	{ m_CurrentAnimationFrame = a_Val; }
		void SetResetFormation(bool a_Val)					{ m_ResetFormation= a_Val; }
		void SetArcLeftTrue(bool a_Val)						{ m_ArcLeft = a_Val; }
		void SetArcPivot(bool a_Val)						{ m_ArcPivot = vec2(
																GetX() + (a_Val? -m_RadiusOfCircle:m_RadiusOfCircle),
																GetY())												;}
		void SetPlayDeathAnimationToFalse()					{ m_PlayBombAnimation = false; }
		/// All the getters		
		GalaxianEnemyEnum GetGalaxianEnemyState() const		{ return m_MyGalaxianEnemyState; }
		AlienEnum GetAlienState() const						{ return m_CurrentAlienState; }
		int GetCurrentAnimationFrame() const				{ return m_CurrentAnimationFrame; }
		float GetScoreGivenOnDeath() const					{ return m_ScoreGivenOnDeath; }
		float GetAnimationRemainderTime() const				{ return m_SecsBetweenFrames; }
		bool GetResetFormation() const						{ return m_ResetFormation; }
		bool GetIsDead() const								{ return m_IsDead; }



	private:
		//Functions for class scope
		void UpdateAnimation(float dt);
		void Move(float dt);
		void Arc(bool arcLeft, float dt);
		void Dive(float dt);
		void Shoot(int a_Xpos, int a_Ypos, float dt);
		void Return(float dt);
		void DeathAnimationUpdate(float dt);
		float lerp(float a, float b, float f);
		

		static const int MISSILEAMOUNT = 3;
		static const int SHOOTCOOLDOWN = 1;
		AlienEnum m_CurrentAlienState;
		GalaxianEnemyEnum m_MyGalaxianEnemyState;
		Missile* m_MissileArray[MISSILEAMOUNT];


		vec2 m_startPosition;
		vec2 m_endPosition;
		vec2 m_ArcPivot;
		int m_FramesForArcing = 0;
		int m_CurrentAnimationFrame = 0;
		int m_CurrentDeathAnimationFrame = 0;
		float m_SecsBetweenFrames = 0.5f;
		float m_SecsBetweenFramesDeath = 0.5f;
		float m_ShootCooldown = 0;
		float m_DiveTime = 0;
		float m_ScoreGivenOnDeath = 5;
		float m_RadiusOfCircle = 20;
		bool m_MoveLeft = true;
		bool m_ArcLeft = false;
		bool m_IsDead = false;
		bool m_ResetFormation = false;
		bool m_ExplosionAnimationPlaying = false;
		bool m_PlayBombAnimation = false;
	};

}