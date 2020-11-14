#include "Shader.h"
#include "Loaders.h"

#include <iostream>

std::map<std::string, Shader> Shader::shaders;

Shader* Shader::CreateShader(std::string name)
{
	if (shaders.find(name) == shaders.end())
	{
		shaders[name] = Shader(name);
	}

	return &shaders[name];
}

void Shader::ClearShaders()
{
	shaders.clear();
}

Shader::Shader(std::string name)
{
	// load shader
	GLchar* vertexShaderSource = Loaders::Loadshader((name + ".vs"));

	GLchar* fragmentShaderSource = Loaders::Loadshader((name + ".fs"));

	GLuint vertexShader = CreateShaderType(vertexShaderSource, GL_VERTEX_SHADER);
	GLuint fragmentShader = CreateShaderType(fragmentShaderSource, GL_FRAGMENT_SHADER);

	delete vertexShaderSource;
	delete fragmentShaderSource;

	m_ShaderProgram = glCreateProgram();

	glAttachShader(m_ShaderProgram, vertexShader);
	glAttachShader(m_ShaderProgram, fragmentShader);
	glLinkProgram(m_ShaderProgram);

	glUseProgram(m_ShaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

Shader::~Shader()
{
	m_Uniforms.clear();
}

GLuint Shader::CreateShaderType(GLchar* shaderCode, GLuint shaderType)
{
	GLuint shader;
	shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderCode, NULL);
	glCompileShader(shader);
	{
		int  success;
		char infoLog[512];
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::" << shaderType <<"::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
	}
	return shader;
}

GLuint Shader::GetShaderProgram()
{
	return m_ShaderProgram;
}

void Shader::AddUniformLocation(std::string uniformName)
{
	GLuint uniformLocation = glGetUniformLocation(m_ShaderProgram, uniformName.c_str());
	m_Uniforms[uniformName] = uniformLocation;
}

void Shader::SetUniform(std::string name, glm::mat4 matrix)
{
	if (m_Uniforms.find(name) != m_Uniforms.end())
	{
		glUniformMatrix4fv(m_Uniforms[name], 1, GL_FALSE, &matrix[0][0]);
	}
	else
	{
		std::cout << "Uniform location " << name << "is not found!" << std::endl;
	}
}
