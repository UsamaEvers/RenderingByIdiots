#include "Background.h"

namespace Tmpl8
{
	Background::Background(Surface* a_Screen)
	{
		for (int i = 0; i < s_AmountOfPixels; i++)
		{
			m_PixelArray[i] = ReSpawn(a_Screen);
		}
	}

	PixelPlot Background::ReSpawn(Surface* a_Screen)
	{
		PixelPlot PP;
		PP.colour = 0;
		unsigned char r = (rand() % 255);
		unsigned char g = (rand() % 255);
		unsigned char b = (rand() % 255);
		PP.colour |= r << (8 * 2);
		PP.colour |= g << (8 * 1);
		PP.colour |= b << (8 * 0);

		PP.lifetime = rand() % 5 + 1.5f;
		PP.Maxlifetime = PP.lifetime;
		PP.Direction = vec2(rand() % 3 - 1,
							rand() % 3 - 1);
		PP.Position  = vec2(rand() % a_Screen->GetWidth(),
							rand() % a_Screen->GetHeight());

		return PP;
	}


	void Background::Update(Surface* a_Screen, float a_DeltaSeconds)
	{
		for (int i = 0; i < s_AmountOfPixels; i++)
		{
			m_PixelArray[i].lifetime -= a_DeltaSeconds * 0.01f;
			float DeathTime = ( m_PixelArray[i].Maxlifetime*0.6f);

			if (m_PixelArray[i].lifetime > DeathTime)
			{
				float LTonMLT = (m_PixelArray[i].lifetime / m_PixelArray[i].Maxlifetime);
				unsigned char b = (m_PixelArray[i].colour >> (8 * 0)) * LTonMLT;
				unsigned char g = (m_PixelArray[i].colour >> (8 * 1)) * LTonMLT;
				unsigned char r = (m_PixelArray[i].colour >> (8 * 2)) * LTonMLT;
				m_PixelArray[i].colour = 0;
				m_PixelArray[i].colour |= r << (8 * 2);
				m_PixelArray[i].colour |= g << (8 * 1);
				m_PixelArray[i].colour |= b << (8 * 0);
			}
			else
			{
				m_PixelArray[i] = ReSpawn(a_Screen);
			}
		}
	}

	void Background::Draw(Surface* a_Screen)
	{
		for (int i = 0; i < s_AmountOfPixels; i++)
		{
			a_Screen->Plot(m_PixelArray[i].Position.x, m_PixelArray[i].Position.y, m_PixelArray[i].colour);
		}
	}


}