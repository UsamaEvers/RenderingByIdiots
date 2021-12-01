#pragma once
#include "GalaxianUI.h"
namespace Tmpl8 {
	class Surface;
	class Entity;
	class AlienManager;
	class GalaxianPlayer;
	class Collision;
	class Background;
	class GalaxianUI;
	
	class Galaxians
	{
	public:
		Galaxians() {}
		~Galaxians() {}
		/// Public Functions
		bool Init(Surface* screen);
		bool Update(Surface* screen,float dt);
		bool Draw(Surface* screen);
	
	private:
		/// Private Functions
		void CheckAlienPlayerCollision();
		void MainMenuHandler(float dt);

		/// Private Variables
		AlienManager* m_TheAlienManager;
		GalaxianPlayer* m_ThePlayer;
		Entity* m_AllEntitiesArray[61];
		Background* m_Background;
		GalaxianUI* m_TheUI;
		GalaxiansGameEnum m_CurrentGameState = GalaxiansGameEnum::GameOverState;		
	};
}