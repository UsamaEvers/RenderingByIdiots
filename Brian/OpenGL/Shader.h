#pragma once
#include <GL\glew.h>
#include <map>
#include <string>

class Shader
{
public:

	Shader() {}
	Shader(std::string name);
	~Shader();

	GLuint GetShaderProgram();

	static Shader* CreateShader(std::string name);
	static void ClearShaders();

private:
	
	GLuint CreateShaderType(GLchar* shaderCode, GLuint shaderType);

	GLuint m_ShaderProgram;
	
	static std::map<std::string, Shader> shaders;

};