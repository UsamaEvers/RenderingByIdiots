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
		bool Init(Surface* screen);
		bool Update(Surface* screen,float dt);
		bool Draw(Surface* screen);
	
	private:
		AlienManager* theAlienManager;
		GalaxianPlayer* Theplayer;// needs to be moved
		Entity* allEntities[100];
		Background* background;
		GalaxianUI* TheUI;
		GalaxiansGameEnum m_CurrentGameState = GalaxiansGameEnum::GameOverState;
		void CheckAlienPlayerCollision();
		void MainMenuHandler(float dt);
		int m_EntitySize = 2;
		
	};

}