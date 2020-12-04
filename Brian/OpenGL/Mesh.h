#pragma once
#include <GL\glew.h>
#include <glm/mat4x4.hpp>
#include <vector>
#include "Shader.h"

class Camera;
class Transform;

struct ModelData
{
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	std::vector<int> indices;
};

class Mesh
{
public:

	Mesh(ModelData modelData);
	~Mesh();

	void Render(Transform transform, Camera cam);

private:
	std::vector<GLuint> m_VBOS;
	GLuint m_VAO;
	GLuint m_EBO;
	GLuint m_NumVertices;
	GLuint m_NumIndices;

	Shader* m_Shader;
};

