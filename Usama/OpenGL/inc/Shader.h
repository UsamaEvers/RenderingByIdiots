#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <map> 
#include <vector>
static enum e_ShaderType
{
	PARTICLESHADER,
	SIMPLESHADER,
	LIGHTCUBESHADER,
	DIFFUSESHADER
};
static enum e_ShaderLocationType
{
	VIEW,
	PROJ,
	COLOR,
	MODEL,
	ID,
	LIGHTPOS,
	CAMERAPOS
};
struct ShaderIDLocations
{
	std::map<e_ShaderLocationType, GLuint> WhichType;
};
class Shader
{
private:
	unsigned int ID;
    void checkCompileErrors(unsigned int shader, std::string type);
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	GLuint getID() const { return ID; }

};
class ShaderManager
{
private:
	void checkCompileErrors(unsigned int shader, std::string type);

	std::map<e_ShaderType, GLuint> allShaders;
	std::map<e_ShaderType, ShaderIDLocations> allTheShaders;
	
	bool i_GenerateAllShaders();
	bool i_GenerateShader(std::vector<std::string> shader, e_ShaderType shadertype);
	bool i_SetUpLocation();
	bool i_SetUpLocation(e_ShaderType shadertype);
	static ShaderManager* instance;

public:
	static void InitShaderManager();
	static GLuint GetShaderID(e_ShaderType shaderType);
	static ShaderIDLocations GetShaderLocations(e_ShaderType shaderType);
};