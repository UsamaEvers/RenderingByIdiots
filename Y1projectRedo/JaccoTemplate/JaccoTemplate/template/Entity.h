#pragma once
namespace Tmpl8 {
	class Surface;
	class Sprite;
	class Entity
	{
	public:
		Entity() {}
		~Entity() {}
		float GetX() { return Xposition; }
		float GetY() { return Yposition; }
		virtual void Draw(Surface* screen) {}
		virtual bool Init(Surface* screen) { return true; }
		virtual void Update(float dt) {}
		Sprite* GetEntity() { return theEntity; }
	protected:
		void SetX(float a_xPos) { Xposition = a_xPos; }
		void SetY(float a_yPos) { Yposition = a_yPos; }
		Sprite* theEntity;
	private:
		float Xposition;
		float Yposition;
		
	};

}