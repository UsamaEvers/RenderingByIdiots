#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
class Shader
{
private:
	unsigned int ID;
    void checkCompileErrors(unsigned int shader, std::string type);
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	GLuint getID() const { return ID; }
};

