#include "Mesh.h"
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include "Camera.h"

Mesh::Mesh(ModelData modelData)
{
	m_NumVertices = static_cast<GLuint>(modelData.vertices.size());

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_NumVertices * sizeof(Vertex), &modelData.vertices[0], GL_STATIC_DRAW);

	m_NumIndices = static_cast<GLuint>(modelData.indices.size());

	glGenBuffers(1, &m_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_NumIndices * sizeof(int), &modelData.indices[0], GL_STATIC_DRAW);

	m_Shader = Shader::CreateShader("shader");
	m_Shader->AddUniformLocation("model");
	m_Shader->AddUniformLocation("view");
	m_Shader->AddUniformLocation("projection");
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
}

void Mesh::Render(Camera cam)
{
	glUseProgram(m_Shader->GetShaderProgram());

	
	glm::mat4 model = m_Transform.GetWorldMatrix();
	glm::mat4 view = cam.GetViewMatrix();
	glm::mat4 projection = cam.GetProjectionMatrix();

	m_Shader->SetUniform("model", model);
	m_Shader->SetUniform("view", view);
	m_Shader->SetUniform("projection", projection);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (float*)(3 * sizeof(float)));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glDrawElements(GL_TRIANGLES, m_NumIndices, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}