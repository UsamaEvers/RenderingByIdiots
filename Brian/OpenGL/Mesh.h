#pragma once

#include <GL\glew.h>
#include <glm/mat4x4.hpp>
#include <vector>
#include "Shader.h"

struct Vertex
{
	glm::vec3 pos;
	glm::vec3 color;
};

class Mesh
{
public:

	Mesh(std::vector<Vertex>& vertices, std::vector<int>& indices);
	~Mesh();

	void Render();

	glm::mat4x4 GetModel();

private:
	GLuint m_VBO;
	GLuint m_EBO;
	GLuint m_NumVertices;
	GLuint m_NumIndices;

	glm::vec3 m_Position;
	glm::vec3 m_Rotation;
	glm::vec3 m_Scale;

	Shader* m_Shader;
};

