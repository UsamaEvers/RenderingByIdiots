#include "Mesh.h"
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<int>& indices) :
	m_Position(0.),
	m_Rotation(0.),
	m_Scale(1.)
{
	m_NumVertices = vertices.size();

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_NumVertices * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	m_NumIndices = indices.size();

	glGenBuffers(1, &m_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices[0], GL_STATIC_DRAW);

	m_Shader = Shader::CreateShader("shader");
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
}

void Mesh::Render()
{
	glUseProgram(m_Shader->GetShaderProgram());

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (float*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glDrawElements(GL_TRIANGLES, m_NumIndices, GL_UNSIGNED_INT, 0);
}

glm::mat4x4 Mesh::GetModel()
{
	return glm::mat4x4(0.);
}