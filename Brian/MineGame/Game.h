#pragma once
#include "Camera.h"

class GLFWwindow;
class Shader;
class Chunk;

class Game
{
public:

	Game();
	~Game();

	int Init();

	void HandleInput();

	void Update();

	//void HandleKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods);

private:

	unsigned int m_Width;
	unsigned int m_Height;

	GLFWwindow* window;
	Shader* m_Shader;

	Camera m_Camera;

	Chunk* m_Chunk;

};

