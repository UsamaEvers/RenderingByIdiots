#include "Chunk.h"
#include "Shader.h"
#include <glm/ext/matrix_transform.hpp>


Chunk::Chunk(Shader* shader)
{
	ModelData modelData = GenerateChunk();
	m_NumVertices = static_cast<GLuint>(modelData.vertices.size());
	m_NumIndices = static_cast<GLuint>(modelData.indices.size());

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	{
		GLuint vboID;

		glGenBuffers(1, &vboID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_NumIndices * sizeof(int), &modelData.indices[0], GL_STATIC_DRAW);
		m_VBOS.push_back(vboID);
	}

	{
		GLuint vboID;
		glGenBuffers(1, &vboID);
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBufferData(GL_ARRAY_BUFFER, m_NumVertices * sizeof(glm::vec3), &modelData.vertices[0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		m_VBOS.push_back(vboID);
	}
	{
		GLuint vboID;
		glGenBuffers(1, &vboID);
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBufferData(GL_ARRAY_BUFFER, modelData.uvs.size() * sizeof(glm::vec2), &modelData.uvs[0], GL_STATIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		m_VBOS.push_back(vboID);
	}
	{
		GLuint vboID;
		glGenBuffers(1, &vboID);
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBufferData(GL_ARRAY_BUFFER, modelData.normals.size() * sizeof(glm::vec3), &modelData.normals[0], GL_STATIC_DRAW);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		m_VBOS.push_back(vboID);
	}
	glBindVertexArray(0);

	m_Shader = shader;
}

Chunk::~Chunk()
{
	for (auto vbo : m_VBOS)
	{
		glDeleteBuffers(1, &vbo);
	}
	glDeleteBuffers(1, &m_EBO);
}

void Chunk::Render()
{
	m_Shader->SetUniform("model", glm::mat4(1.));

	glBindVertexArray(m_VAO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glDrawElements(GL_TRIANGLES, m_NumIndices, GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

ModelData GenerateFace(glm::vec3 rotation, float angle)
{
	ModelData data;
	std::vector<glm::vec3> vertices = { {.5, .5, .5},  {-.5, .5, .5}, {-.5, -.5, .5}, {.5, -.5, .5} };
	std::vector<glm::vec2> uvs = { {1., 0. }, {0., 0.}, {0., 1.},  {1., 1.} };
	std::vector<int> indices = { 0, 1, 3, 1, 2, 3 };
	std::vector<glm::vec3> normals = { {0., 0., -1.}, {0., 0., -1.}, {0., 0., -1.}, {0., 0., -1.} };

	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.), angle, rotation);

	for (int i = 0; i < 4; i++)
	{
		vertices[i] = glm::vec4(vertices[i], 1.) * rotationMatrix;
		normals[i] = glm::vec4(normals[i], 0.) * rotationMatrix;
	}

	data.vertices = vertices;
	data.uvs = uvs;
	data.normals = normals;
	data.indices = indices;
	return data;
}

ModelData Chunk::GenerateChunk()
{
	ModelData data;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<int> indices;
	std::vector<glm::vec3> normals;	

	int index = 0;
	glm::vec3 angleAxis[6] = {
		{0., 1., 0},
		{0., 1., 0},
		{0., 1., 0},
		{0., 1., 0},
		{1., 0., 0},
		{1., 0., 0}
	};
	float angles[6] = {
		0.f,
		 .5f,
		1.f,
		1.5f,
		.5,
		1.5f
	};
	for(int i = 0; i < 6; i++)
	{
		ModelData face = GenerateFace(angleAxis[i], angles[i]*glm::pi<float>());
		for (int i = 0; i < 4; i++)
		{
			vertices.push_back(face.vertices[i]);
			uvs.push_back(face.uvs[i]);
			normals.push_back(face.normals[i]);
		}
		for (int i = 0; i < 6; i++)
		{
			indices.push_back(face.indices[i] + index);
		}
		index += 6;
	}

	data.vertices = vertices;
	data.uvs = uvs;
	data.normals = normals;
	data.indices = indices;
	return data;
}