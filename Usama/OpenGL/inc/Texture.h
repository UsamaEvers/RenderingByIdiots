#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <vector>
#include <GLFW/glfw3.h>
#include <map> 

class TextureManager
{
private:
	TextureManager();
	~TextureManager() {}

	static TextureManager* instance;
	GLuint i_CheckIfTextureExists(std::string textName, bool alphaEnable);
	bool i_GenTexture(std::string textName, bool alphaEnable);
	std::map<std::string, GLuint> allTextures;
public:
	static void InitTextureManager();
	static GLuint CheckIfTextureExists(std::string textName, bool alphaEnable);
};