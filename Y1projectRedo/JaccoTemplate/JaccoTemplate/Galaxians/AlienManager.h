#pragma once
#include "../template/template.h"
namespace Tmpl8
{
	class Alien;
	class Surface;
	class Entity;
	const int X = 6;
	const int Y = 10;
	class GalaxianPlayer;
	
	class AlienManager
	{
	public:
		AlienManager() {}
		~AlienManager() {}
		bool Init(Surface* a_Screen, GalaxianPlayer* a_Player,  Entity* a_EntityArray[],int a_ArrayOffset);
		void Update(Surface* a_Screen,float dt);
		void ResetAliens(float dt);

		/// Get Functions
		Alien** GetAlienArray() const { return m_AlienArray; }

	private:
		/// Private functions
		void ReturnToFormation();
		void FormationMove(Surface* a_Screen, float dt);
		void StateChange(float dt);
		void ResetFormation(float dt);
		vec2 CalculateReturnPositions(int a_It);
		int CheckRightColumn(int a_ItMin, int a_ItMax);
		int CheckLeftColumn(int a_ItMin, int a_ItMax, int a_Width);
		int CheckRightColumnState(int a_ItMin, int a_ItMax);
		int CheckLeftColumnState(int a_ItMin, int a_ItMax);
	

		/// Private variables
		Alien** m_AlienArray;
		GalaxianPlayer* m_ThePlayer;
		
		float m_Timer= 2;
		float m_HalfOfScreenWidth = 0;
		bool m_AlienSent = false;
		bool m_LeftDirection = true;

	};

}