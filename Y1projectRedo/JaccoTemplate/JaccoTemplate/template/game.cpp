#include "game.h"
#include "Input.h"
#include "surface.h"
#include "template.h"
#include <cstdio> //printf
#include "SDL2-2.0.3/include/SDL_keycode.h"
#include "../Galaxians/Galaxians.h"
namespace Tmpl8
{



	void Game::Init()
	{

	}

	void Game::Shutdown()
	{
	}
	enum class CurrentGameEnum
	{
		e_Galaxian = 0,
		e_Gauntlet,
		e_StartScreen
	};
	CurrentGameEnum currentGame = CurrentGameEnum::e_StartScreen;

	//Sprite GalaxiansCover(new Surface("assets/GalaxiansCover.jpg"), 1);
	//Sprite GauntletCover(new Surface("assets/GauntletCover.jpg"), 1);
	//vec2 GalaxiansPos(ScreenWidth / 4 - GalaxiansCover.GetWidth() / 4, ScreenHeight / 8);
	//vec2 GauntletPos(ScreenWidth / 1.5f - GauntletCover.GetWidth() / 4, ScreenHeight / 8);
	bool isgalaxians = true;
	void Game::KeyDown(int key)
	{
		Input::SetKey(key, true);

		if (CurrentGameEnum::e_StartScreen == currentGame)
		{
			switch (key)
			{
			case 79:			//Highlight Right
			//	GauntletPos.y = (ScreenHeight / 8) - 50;
			//	GalaxiansPos.y = (ScreenHeight / 8) + 50;
				isgalaxians = false;
				break;
			case 80:			//Highlight Left
			//	GauntletPos.y = (ScreenHeight / 8) + 50;
			//	GalaxiansPos.y = (ScreenHeight / 8) - 50;
				isgalaxians = true;
				break;
			case 44:			//Select
				if (!isgalaxians)
					currentGame = CurrentGameEnum::e_Gauntlet;
				else
					currentGame = CurrentGameEnum::e_Galaxian;
				break;
			case 40:			//Select
				if (!isgalaxians)
					currentGame = CurrentGameEnum::e_Gauntlet;
				else
					currentGame = CurrentGameEnum::e_Galaxian;
				break;
			default:
				break;
			}

		}
	}

	void Game::KeyUp(int key)
	{
		Input::SetKey(key, false);
	}

	//Surface gayfaghomoshit (ScreenWidth/10,ScreenHeight/10);
	//Sprite gayfaghomoshitsprite(&gayfaghomoshit,1);
	Galaxians* GalaxianGame;

	Surface* renderingSurface = new Surface(ScreenWidth / 4, ScreenHeight / 4);
	Sprite renderingSprite(renderingSurface, 1);
	void Game::Tick(float deltaTime)
	{
		renderingSurface->Clear(0);
		screen->Clear(0);

		//if (CurrentGameEnum::e_StartScreen == currentGame)
		//{
		//	//FontSurface->Print("hello world", 0, 0, 0xffffff);
		//	//FontSprite.DrawScaled(0, 0, screen->GetWidth(), screen->GetHeight(), screen);

		//	//	GalaxiansCover.DrawScaled(GalaxiansPos.x, GalaxiansPos.y, ScreenWidth / 2, ScreenHeight / 2, screen);
		//	//	GauntletCover.DrawScaled(GauntletPos.x, GauntletPos.y, ScreenWidth / 2, ScreenHeight / 2, screen);
		//}
		//else if (CurrentGameEnum::e_Galaxian == currentGame)
		//{

			if (isgalaxians) // Find a better way to init the game and not have it in the tick loop
			{
				GalaxianGame = new Galaxians();
				GalaxianGame->Init(renderingSurface);
				isgalaxians = false;
			}
			GalaxianGame->Update(renderingSurface, deltaTime);
			GalaxianGame->Draw(renderingSurface);


			renderingSprite.DrawScaled(0, 0, screen->GetWidth(), screen->GetHeight(), screen);
	//	}

	}
};