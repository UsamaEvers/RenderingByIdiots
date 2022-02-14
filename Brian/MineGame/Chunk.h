#pragma once
#include <GL\glew.h>
#include <glm/mat4x4.hpp>
#include <vector>

class Shader;

struct ModelData
{
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	std::vector<int> indices;
};

class Chunk
{
public:

	Chunk(Shader* shader);
	~Chunk();

	void Render();

private:
	ModelData GenerateChunk();

	std::vector<GLuint> m_VBOS;
	GLuint m_VAO;
	GLuint m_EBO;
	GLuint m_NumVertices;
	GLuint m_NumIndices;

	Shader* m_Shader;
};