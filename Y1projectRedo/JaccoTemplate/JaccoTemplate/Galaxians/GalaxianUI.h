#pragma once
#include"../template/template.h"
#include"../template/surface.h"

#include <iostream>
#include <string>
namespace Tmpl8
{
	class Sprite;

	enum class GalaxiansGameEnum
	{
		GameLoadState = 0,
		GameInfoState,
		GameStartState,
		GameActiveState,
		GameOverState,
		GameAlwaysState
	};
	struct Text
	{
		GalaxiansGameEnum MyCurrentState;
		Pixel Colour;
		vec2 Position;
		std::string text;
		int value = -1;
		bool Render = false;
	};
	struct SpriteUI
	{
		~SpriteUI() { theSprite = nullptr; delete theSprite; }
		GalaxiansGameEnum MyCurrentState;
		Sprite* theSprite;
		vec2 Position;
		bool render = false;
	};
	class GalaxianUI
	{
	public:
		GalaxianUI() {}
		~GalaxianUI() {}

		/// Public Vars
		void Init(Surface* a_Screen, int a_MaxPlayerHealth);
		void Update(GalaxiansGameEnum currentState, float a_DT, int a_playerScore);
		void Draw(Surface* a_Screen);
		void UpdatePlayerHealth(int a_Val) { m_CurrentPlayerHealth = a_Val; }
		GalaxiansGameEnum GalaxiansGameEnumState(GalaxiansGameEnum* currentState);
		
		/// Enable|Disable
		Text EnableText(int a_Iterator);
		Text EnableText(std::string a_Text);
		Text DisableText(int a_Iterator);
		Text DisableText(std::string a_Text);

	private:
		/// Private functions
		void UpdateScore(float a_DT, int a_playerScore);
		void RenderCurrentState(GalaxiansGameEnum currentState, float a_dt);
		
		/// Private variables
		static const int s_MaxAmountOfText = 100;
		static const int s_MaxAliens = 4;
		int m_CurrentPlayerHealth = 0;
		int m_screenwidth = 0;
		float m_TimerToRemovePlayerOneText = 5.f;
		bool m_ExtraZero = false;
		bool m_PassedZeros[5] = { false };

		Text TextArray[s_MaxAmountOfText];
		SpriteUI* m_AlienUI[s_MaxAliens];
		SpriteUI* m_PlayerHealthUI[];

	};
}

