#include "Shader.h"

#include <fstream>
#include <iostream>
#include <vector>

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

size_t split(const std::string& txt, std::vector<std::string>& strs, char ch)
{
	size_t pos = txt.find(ch);
	size_t initialPos = 0;
	strs.clear();

	// Decompose statement
	while (pos != std::string::npos) {
		strs.push_back(txt.substr(initialPos, pos - initialPos));
		initialPos = pos + 1;

		pos = txt.find(ch, initialPos);
	}

	// Add the last one
	strs.push_back(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));

	return strs.size();
}

char* Loadshader(std::string filename)
{
	unsigned long len;
	std::ifstream file;
	file.open(filename, std::ios::in); // opens as ASCII!

	len = getFileLength(file);

	char* ShaderSource;

	ShaderSource = (char*) new char[len + 1];

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
	GLchar* vertexShaderSource = Loadshader((name + ".vs"));

	GLchar* fragmentShaderSource = Loadshader((name + ".fs"));

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
			std::cout << "ERROR::SHADER::" << shaderType << "::COMPILATION_FAILED\n" << infoLog << std::endl;
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

void Shader::SetUniform(std::string name, glm::vec3 val)
{
	if (m_Uniforms.find(name) != m_Uniforms.end())
	{
		glUniform3fv(m_Uniforms[name], 1, &val[0]);
	}
	else
	{
		std::cout << "Uniform location " << name << "is not found!" << std::endl;
	}
}
