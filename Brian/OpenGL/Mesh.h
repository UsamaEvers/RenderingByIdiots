#pragma once

#include <GL\glew.h>
#include <glm/mat4x4.hpp>
#include <vector>
#include "Shader.h"
#include "Transform.h"

class Camera;

struct Vertex
{
	glm::vec3 pos;
	glm::vec2 uv;
};

struct ModelData
{
	std::vector<Vertex> vertices;
	std::vector<int> indices;
};

class Mesh
{
public:

	Mesh(ModelData modelData);
	~Mesh();

	void Render(Camera cam);
	
	Transform& GetTransform() { return m_Transform; };

private:
	GLuint m_VBO;
	GLuint m_EBO;
	GLuint m_NumVertices;
	GLuint m_NumIndices;

	Transform m_Transform;

	Shader* m_Shader;
};

