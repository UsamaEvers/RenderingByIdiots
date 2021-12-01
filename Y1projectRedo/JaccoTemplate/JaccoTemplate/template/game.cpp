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
		renderingSurface = new Surface(ScreenWidth / 4, ScreenHeight / 4);
		renderingSprite = new Sprite(renderingSurface, 1);
		GalaxianGame = new Galaxians();
		GalaxianGame->Init(renderingSurface);
	}

	void Game::Shutdown()
	{
		screen = nullptr;
		delete screen;	

		GalaxianGame = nullptr;
		delete GalaxianGame;

		renderingSurface = nullptr;
		delete renderingSurface;

		renderingSprite = nullptr;
		delete renderingSprite;
	}

	void Game::KeyDown(int key)
	{
		Input::SetKey(key, true);
	}

	void Game::KeyUp(int key)
	{
		Input::SetKey(key, false);
	}

	void Game::Tick(float deltaTime)
	{
		renderingSurface->Clear(0);
		screen->Clear(0);

		GalaxianGame->Update(renderingSurface, deltaTime);
		GalaxianGame->Draw(renderingSurface);
		renderingSprite->DrawScaled(0, 0, screen->GetWidth(), screen->GetHeight(), screen);
	}
};