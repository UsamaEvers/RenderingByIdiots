#include "GalaxianUI.h"
using namespace Tmpl8;
const int PLAYERSCOREITERATOR = 2;
const int HIGHSCOREITERATOR = 3;

void Tmpl8::GalaxianUI::Init(Surface* a_Screen, int a_MaxPlayerHealth)
{

	m_CurrentPlayerHealth = a_MaxPlayerHealth;
	m_screenwidth = a_Screen->GetWidth();
	unsigned int currentIndex = 0;
	Text text;
	//1UP
	text.Render = true;
	text.Colour = 0xffffff;
	text.Position = vec2(a_Screen->GetWidth() * 0.15f, 0.f);
	text.text = "1UP";
	text.MyCurrentState = GalaxiansGameEnum::GameAlwaysState;
	TextArray[currentIndex++] = text;

	//HIGH SCORE
	text.Position = vec2(a_Screen->GetWidth() * 0.357f, 0.f);
	text.text = "HIGH SCORE";
	TextArray[currentIndex++] = text;

	//Player Score	RED
	text.Colour = 0xff0000;
	text.value = 00;
	text.text = "00";
	text.Position = vec2(a_Screen->GetWidth() * 0.2f, 5.f);
	TextArray[currentIndex++] = text;

	//High Score	RED
	text.Position = vec2(a_Screen->GetWidth() * 0.525f, 5.f);
	TextArray[currentIndex++] = text;

	// CREDIT  0
	text.Colour = 0X00b1d4;
	text.value = -1;
	text.Position = vec2(a_Screen->GetWidth() * 0.125f, a_Screen->GetHeight() * 0.97f);
	text.text = "CREDIT  ";
	text.MyCurrentState = GalaxiansGameEnum::GameOverState;
	TextArray[currentIndex++] = text;

	// credit value
	text.Colour = 0X00b1d4;
	text.value = 0;
	text.Position = vec2(a_Screen->GetWidth() * 0.35f, a_Screen->GetHeight() * 0.97f);
	text.text = "0";
	TextArray[currentIndex++] = text;




	// CREDIT  0
	text.Colour = 0X00b1d4;
	text.value = -1;
	text.Position = vec2(a_Screen->GetWidth() * 0.125f, a_Screen->GetHeight() * 0.97f);
	text.text = "CREDIT  ";
	text.MyCurrentState = GalaxiansGameEnum::GameStartState;
	TextArray[currentIndex++] = text;

	// credit value
	text.Colour = 0X00b1d4;
	text.value = 1;
	text.Position = vec2(a_Screen->GetWidth() * 0.35f, a_Screen->GetHeight() * 0.97f);
	text.text = "1";
	TextArray[currentIndex++] = text;

	// CREDIT  0
	text.Colour = 0X00b1d4;
	text.value = -1;
	text.Position = vec2(a_Screen->GetWidth() * 0.125f, a_Screen->GetHeight() * 0.97f);
	text.text = "CREDIT  ";
	text.MyCurrentState = GalaxiansGameEnum::GameInfoState;
	TextArray[currentIndex++] = text;

	// credit value
	text.Colour = 0X00b1d4;
	text.value = 0;
	text.Position = vec2(a_Screen->GetWidth() * 0.35f, a_Screen->GetHeight() * 0.97f);
	text.text = "0";
	TextArray[currentIndex++] = text;

	//WE ARE THE GALAXIANS
	text.Colour = 0xff0000;
	text.value = -1;
	text.Position = vec2(a_Screen->GetWidth() * 0.2f, a_Screen->GetHeight() * 0.25f);
	text.text = "WE ARE THE GALAXIANS";
	text.MyCurrentState = GalaxiansGameEnum::GameInfoState;
	TextArray[currentIndex++] = text;

	//MISSION: DESTROY ALIENS
	text.Colour = 0xff0000;
	text.value = -1;
	text.Position = vec2(a_Screen->GetWidth() * 0.15f, a_Screen->GetHeight() * 0.3f);
	text.text = "MISSION: DESTROY ALIENS";
	TextArray[currentIndex++] = text;

	// - SCORE ADVANCE TABLE -
	text.Colour = 0Xffffff;
	text.value = -1;
	text.Position = vec2(a_Screen->GetWidth() * 0.15f, a_Screen->GetHeight() * 0.5f);
	text.text = "- SCORE ADVANCE TABLE -";
	TextArray[currentIndex++] = text;

	// CONVOY CHARGER
	text.Colour = 0X00b1d4;
	text.value = -1;
	text.Position = vec2(a_Screen->GetWidth() * 0.269f, a_Screen->GetHeight() * 0.55f);
	text.text = "CONVOY  CHARGER";
	TextArray[currentIndex++] = text;


	// 60 80 PTS
	text.Colour = 0X00b1d4;
	text.value = -1;
	text.Position = vec2(a_Screen->GetWidth() * 0.324f, a_Screen->GetHeight() * 0.6f);
	text.text = "60      200  pts";
	TextArray[currentIndex++] = text;

	// 50 80 PTS
	text.Colour = 0X00b1d4;
	text.value = -1;
	text.Position = vec2(a_Screen->GetWidth() * 0.324f, a_Screen->GetHeight() * 0.65f);
	text.text = "50      100  pts";
	TextArray[currentIndex++] = text;

	// 40 80 PTS
	text.Colour = 0X00b1d4;
	text.value = -1;
	text.Position = vec2(a_Screen->GetWidth() * 0.324f, a_Screen->GetHeight() * 0.7f);
	text.text = "40       80  pts";
	TextArray[currentIndex++] = text;

	// 30 80 PTS
	text.Colour = 0X00b1d4;
	text.value = -1;
	text.Position = vec2(a_Screen->GetWidth() * 0.324f, a_Screen->GetHeight() * 0.75f);
	text.text = "30       60  pts";
	TextArray[currentIndex++] = text;

	// PUSH START BUTTON
	text.Colour = 0X00b1d4;
	text.value = -1;
	text.Position = vec2(a_Screen->GetWidth() * 0.225f, a_Screen->GetHeight() * 0.55f);
	text.text = "PUSH START BUTTON";
	text.Render = false;
	text.MyCurrentState = GalaxiansGameEnum::GameStartState;
	TextArray[currentIndex++] = text;

	// BONUS GALAXIP FOR 20000 pts
	text.Colour = 0X00b1d4;
	text.value = -1;
	text.Position = vec2(a_Screen->GetWidth() * 0.09f, a_Screen->GetHeight() * 0.725f);
	text.text = "BONUS GALAXIP FOR 20000 pts";
	TextArray[currentIndex++] = text;

	// GAME OVER
	text.Colour = 0XFF0000;
	text.value = -1;
	text.Position = vec2(a_Screen->GetWidth() * 0.357f, a_Screen->GetHeight() * 0.675f);
	text.text = "GAME OVER";
	text.Render = true;
	text.MyCurrentState = GalaxiansGameEnum::GameOverState;
	TextArray[currentIndex++] = text;

	// Player One
	text.Colour = 0XFF0000;
	text.value = -1;
	text.Position = vec2(a_Screen->GetWidth() * 0.357f, a_Screen->GetHeight() * 0.675f);
	text.text = "Player One";
	text.Render = true;
	text.MyCurrentState = GalaxiansGameEnum::GameActiveState;
	TextArray[currentIndex++] = text;


	for (int i = 0; i < a_MaxPlayerHealth; i++)
	{
		SpriteUI* tempSprite = new SpriteUI();
		tempSprite->theSprite = new Sprite(new Surface("assets/shooter_live.png"), 1);
		tempSprite->render = false;
		tempSprite->MyCurrentState = GalaxiansGameEnum::GameActiveState;
		tempSprite->Position = vec2(a_Screen->GetWidth() * (i * 0.075f), a_Screen->GetHeight() * 0.9f);
		m_PlayerHealthUI[i] = tempSprite;
	}
	unsigned int alienIndex = 0;

	for (int i = 0; i < s_MaxAliens; i++)
	{
		SpriteUI* tempSprite = new SpriteUI();
		tempSprite->render = false;
		tempSprite->MyCurrentState = GalaxiansGameEnum::GameInfoState;
		float a = 0.05f * i;
		tempSprite->Position = vec2(a_Screen->GetWidth() * 0.2f, a_Screen->GetHeight() * (0.735f - a));
 		m_AlienUI[i] = tempSprite;
	}
	{
		m_AlienUI[0]->theSprite = new Sprite(new Surface("assets/galaxianC.png"), 2);
		m_AlienUI[1]->theSprite = new Sprite(new Surface("assets/galaxianB.png"), 2);
		m_AlienUI[2]->theSprite = new Sprite(new Surface("assets/galaxianA.png"), 2);
		m_AlienUI[3]->theSprite = new Sprite(new Surface("assets/elite.png"), 1);
	}
	
}
void Tmpl8::GalaxianUI::Update(GalaxiansGameEnum currentState, float a_DT, int a_playerScore)
{
	RenderCurrentState(currentState, a_DT);
	UpdateScore(a_DT, a_playerScore);
}

void Tmpl8::GalaxianUI::Draw(Surface* a_Screen)
{
	for (int i = 0; i < s_MaxAmountOfText; i++)
	{
		if (TextArray[i].Render) {
			if (TextArray[i].value != -1)
			{
				TextArray[i].text = std::to_string(TextArray[i].value);
				//TextArray[i].value += 1;
			}
			char* chrtext = new char[TextArray[i].text.length() + 1];
			strcpy(chrtext, TextArray[i].text.c_str());
			a_Screen->Print(chrtext,
				TextArray[i].Position.x,
				TextArray[i].Position.y,
				TextArray[i].Colour);

			chrtext = nullptr;
			delete chrtext;
		}
	}
	for (int i = 0; i < m_CurrentPlayerHealth; i++)
	{
		if (m_PlayerHealthUI[i]->render)
		{
			m_PlayerHealthUI[i]->theSprite->Draw(a_Screen,
				m_PlayerHealthUI[i]->Position.x,
				m_PlayerHealthUI[i]->Position.y);
		}
	}
	for (int i = 0; i < s_MaxAliens; i++)
	{
		if (m_AlienUI[i]->render)
		{
			m_AlienUI[i]->theSprite->Draw(a_Screen,
				m_AlienUI[i]->Position.x,
				m_AlienUI[i]->Position.y);
		}
	}
}

GalaxiansGameEnum Tmpl8::GalaxianUI::GalaxiansGameEnumState(GalaxiansGameEnum* currentState)
{
	switch (*currentState)
	{
	case Tmpl8::GalaxiansGameEnum::GameLoadState:
		*currentState = GalaxiansGameEnum::GameInfoState;
		break;
	case Tmpl8::GalaxiansGameEnum::GameInfoState:
		*currentState = GalaxiansGameEnum::GameStartState;
		break;
	case Tmpl8::GalaxiansGameEnum::GameStartState:
		*currentState = GalaxiansGameEnum::GameActiveState;
		break;
	case Tmpl8::GalaxiansGameEnum::GameActiveState:
		*currentState = GalaxiansGameEnum::GameOverState;
		break;
	case Tmpl8::GalaxiansGameEnum::GameOverState:
		*currentState = GalaxiansGameEnum::GameInfoState;
		break;
	default:
		break;
	}

	return *currentState;
}

void Tmpl8::GalaxianUI::UpdateScore(float a_DT, int a_playerScore)
{
	TextArray[PLAYERSCOREITERATOR].value = a_playerScore;
	bool AddForHS = false;
	if (TextArray[PLAYERSCOREITERATOR].value > TextArray[HIGHSCOREITERATOR].value)
	{
		TextArray[HIGHSCOREITERATOR].value = a_playerScore;
		AddForHS = true;
	}

	if (a_playerScore >= 100)
	{
		if (!m_PassedZeros[0])
		{
			m_PassedZeros[0] = true;
			TextArray[PLAYERSCOREITERATOR].Position = vec2((float)m_screenwidth * 0.175f, 5.f);
			if (AddForHS)
				TextArray[HIGHSCOREITERATOR].Position = vec2((float)m_screenwidth * 0.5f, 5.f);
		}
		//check one more
		if (a_playerScore >= 1000)
		{
			if (!m_PassedZeros[1])
			{
				m_PassedZeros[1] = true;
				TextArray[PLAYERSCOREITERATOR].Position = vec2((float)m_screenwidth * 0.15f, 5.f);
				if (AddForHS)
					TextArray[HIGHSCOREITERATOR].Position = vec2((float)m_screenwidth * 0.475f, 5.f);
			}
			//check one more
			if (a_playerScore >= 1000)
			{
				if (!m_PassedZeros[2])
				{
					m_PassedZeros[2] = true;
					TextArray[PLAYERSCOREITERATOR].Position = vec2((float)m_screenwidth * 0.125f, 5.f);
					if (AddForHS)
						TextArray[HIGHSCOREITERATOR].Position = vec2((float)m_screenwidth * 0.45f, 5.f);
				}
				//check one more
				if (a_playerScore >= 10000)
				{
					if (!m_PassedZeros[3])
					{
						m_PassedZeros[3] = true;
						TextArray[PLAYERSCOREITERATOR].Position = vec2((float)m_screenwidth * 0.1f, 5.f);
						if (AddForHS)
							TextArray[HIGHSCOREITERATOR].Position = vec2((float)m_screenwidth * 0.425f, 5.f);
					}
					//check one more
					if (a_playerScore >= 100000)
					{
						if (!m_PassedZeros[4])
						{
							m_PassedZeros[4] = true;
							TextArray[PLAYERSCOREITERATOR].Position = vec2((float)m_screenwidth * 0.075f, 5.f);
							if (AddForHS)
								TextArray[HIGHSCOREITERATOR].Position = vec2((float)m_screenwidth * 0.4f, 5.f);
						}
					}
				}
			}
		}
	}

	if (TextArray[PLAYERSCOREITERATOR].value > TextArray[HIGHSCOREITERATOR].value)
	{
		TextArray[HIGHSCOREITERATOR].value = a_playerScore;
	}

}
void Tmpl8::GalaxianUI::RenderCurrentState(GalaxiansGameEnum currentState, float a_dt)
{
	for (int i = 0; i < s_MaxAmountOfText; i++)
	{
		//Render the correct text
		if (currentState == TextArray[i].MyCurrentState)
		{
			TextArray[i].Render = true;
		}
		else if (currentState != TextArray[i].MyCurrentState)
		{
			switch (TextArray[i].MyCurrentState)
			{
			case Tmpl8::GalaxiansGameEnum::GameLoadState:
				TextArray[i].Render = false;
				break;
			case Tmpl8::GalaxiansGameEnum::GameInfoState:
				TextArray[i].Render = false;
				break;
			case Tmpl8::GalaxiansGameEnum::GameStartState:
				TextArray[i].Render = false;
				break;
			case Tmpl8::GalaxiansGameEnum::GameActiveState:
				TextArray[i].Render = false;
				break;
			case Tmpl8::GalaxiansGameEnum::GameOverState:
				TextArray[i].Render = false;
				break;
			default:
				break;
			}
		}

		//Removes player one after a bit.
		if (currentState == GalaxiansGameEnum::GameActiveState)
		{
			m_TimerToRemovePlayerOneText -= a_dt * 0.001f;
			if (m_TimerToRemovePlayerOneText < 0)
			{
				DisableText("Player One");
			}
		}
	}
	for (int i = 0; i < m_CurrentPlayerHealth; i++)
	{
		if (currentState == m_PlayerHealthUI[i]->MyCurrentState)
		{
			m_PlayerHealthUI[i]->render  = true;
		}
		else
		{
			m_PlayerHealthUI[i]->render = false;

		}
	}
	for (int i = 0; i < s_MaxAliens; i++)
	{
		if (currentState == m_AlienUI[i]->MyCurrentState)
		{
			m_AlienUI[i]->render = true;
		}
		else
		{
			m_AlienUI[i]->render = false;
		}
	}
}

