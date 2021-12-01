#pragma once
#include  "../template/template.h"
#include  "../template/Surface.h"

namespace Tmpl8
{
	struct PixelPlot
	{
		Pixel colour;
		vec2 Position;
		vec2 Direction;
		float lifetime;
		float Maxlifetime;
		
	};
	class Background
	{
	public:
		Background(Surface* a_Screen);
		~Background() {}
		/// Public Functions
		PixelPlot ReSpawn(Surface* a_Screen);
		void Update(Surface* a_Screen, float a_DeltaSeconds);
		void Draw(Surface* a_Screen);
	private:
		/// Private Variables
		static const int s_AmountOfPixels = 100;
		PixelPlot m_PixelArray[s_AmountOfPixels];
	};
}