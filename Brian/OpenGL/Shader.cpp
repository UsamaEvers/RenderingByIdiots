#include "Shader.h"
#include <iostream>
#include <fstream>

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

unsigned long getFileLength(std::ifstream& file)
{
	if (!file.good()) return 0;

	unsigned long pos = file.tellg();
	file.seekg(0, std::ios::end);
	unsigned long len = file.tellg();
	file.seekg(std::ios::beg);

	return len;
}

GLchar* loadshader(const char* filename)
{
	unsigned long len;
	std::ifstream file;
	file.open(filename, std::ios::in); // opens as ASCII!
	
	len = getFileLength(file);

	GLchar* ShaderSource;

	ShaderSource = (GLchar*) new char[len + 1];
	
	 // len isn't always strlen cause some characters are stripped in ascii read...
	 // it is important to 0-terminate the real length later, len is just max possible value... 
	ShaderSource[len] = 0;

	unsigned int i = 0;
	while (file.good())
	{
		ShaderSource[i] = file.get();       // get character from file.
		if (!file.eof())
			i++;
	}

	ShaderSource[i] = 0;  // 0-terminate it at the correct position

	file.close();

	return ShaderSource;
}

Shader::Shader(std::string name)
{
	// load shader
	GLchar* vertexShaderSource = loadshader((name + ".vs").c_str() );

	GLchar* fragmentShaderSource = loadshader((name + ".fs").c_str());

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
{}

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