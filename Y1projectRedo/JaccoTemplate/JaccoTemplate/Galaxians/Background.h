#pragma once
#include  "../template/template.h"
#include  "../template/Surface.h"

namespace Tmpl8
{
	struct PixelPlot
	{
		Pixel colour;
		float lifetime;
		float Maxlifetime;
		vec2 Position;
		vec2 Direction;
	};
	class Background
	{
	public:
		Background(Surface* a_Screen);
		~Background() {}

		PixelPlot ReSpawn(Surface* a_Screen);
		void Update(Surface* a_Screen, float a_DeltaSeconds);
		void Draw(Surface* a_Screen);
	private:
		static const int s_AmountOfPixels = 100;
		PixelPlot m_PixelArray[s_AmountOfPixels];
	};
}