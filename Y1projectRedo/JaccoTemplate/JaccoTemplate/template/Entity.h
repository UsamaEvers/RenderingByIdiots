#pragma once
namespace Tmpl8 {
	class Surface;
	class Sprite;
	class Entity
	{
	public:
		Entity() {}
		~Entity() {
			m_TheEntity = nullptr;
			delete m_TheEntity;
		}
		
		/// Public Functions
		virtual void Draw(Surface* screen) {}
		virtual bool Init(Surface* screen) { return true; }
		virtual void Update(float dt) {}
		
		/// Getters
		Sprite* GetEntity() { return m_TheEntity; }
		float GetX() { return m_XPosition; }
		float GetY() { return m_YPosition; }
	protected:
		/// Protected Functions/Variables
		void SetX(float a_xPos) { m_XPosition = a_xPos; }
		void SetY(float a_yPos) { m_YPosition = a_yPos; }
		Sprite* m_TheEntity;

	private:
		/// Private Variables
		float m_XPosition;
		float m_YPosition;
		
	};

}