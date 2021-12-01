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
		Alien** GetAlienArray() const { return m_AlienArray; }
		void ResetAliens(float dt);
	private:
		void ReturnToFormation();
		void FormationMove(Surface* a_Screen, float dt);
		void StateChange(float dt);
		void ResetFormation(float dt);
		int CheckRightColumn(int a_ItMin, int a_ItMax);
		int CheckLeftColumn(int a_ItMin, int a_ItMax, int a_Width);
		int CheckRightColumnState(int a_ItMin, int a_ItMax);
		int CheckLeftColumnState(int a_ItMin, int a_ItMax);
		
		vec2 CalculateReturnPositions(int a_It);
		bool leftDirection = true;
		Alien** m_AlienArray;
		GalaxianPlayer* thePlayer;
		
		float timer= 2;
		float m_HalfOfScreenWidth = 0;
		bool alienSent = false;
		int alienManagerArray[X][Y]
		{
			{0, 0, 0, 4, 0, 0, 4, 0, 0, 0},
			{0, 0, 3, 3, 3, 3, 3, 3, 0, 0},
			{0, 2, 2, 2, 2, 2, 2, 2, 2, 0},
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1} 
		};
	};

}