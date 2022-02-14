#pragma once
#include <GL\glew.h>
#include <glm/matrix.hpp>

#include <map>
#include <string>

class Shader
{
public:
	static Shader* CreateShader(std::string name);
	static void ClearShaders();
private:
	static std::map<std::string, Shader> shaders;
public:

	Shader() {};

	Shader(std::string name);
	~Shader();

	GLuint GetShaderProgram();

	void AddUniformLocation(std::string uniformName);

	void SetUniform(std::string name, glm::mat4 matrix);

	void SetUniform(std::string name, glm::vec3 val);

private:

	GLuint CreateShaderType(GLchar* shaderCode, GLuint shaderType);

	GLuint m_ShaderProgram;

	std::map<std::string, GLuint> m_Uniforms;

};