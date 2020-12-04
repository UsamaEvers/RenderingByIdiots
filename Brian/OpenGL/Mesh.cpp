#include "Mesh.h"

#include "Camera.h"
#include "Transform.h"

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>


Mesh::Mesh(ModelData modelData)
{

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

	m_Shader = Shader::CreateShader("shader");
	m_Shader->AddUniformLocation("model");
	m_Shader->AddUniformLocation("view");
	m_Shader->AddUniformLocation("projection");
	m_Shader->AddUniformLocation("uEyePosition");
	m_Shader->AddUniformLocation("uColor");
	m_Shader->AddUniformLocation("uCool");
	m_Shader->AddUniformLocation("uWarm");
}

Mesh::~Mesh()
{
	for (auto vbo : m_VBOS)
	{
		glDeleteBuffers(1, &vbo);
	}
	glDeleteBuffers(1, &m_EBO);
}

void Mesh::Render(Transform transform, Camera cam)
{
	glUseProgram(m_Shader->GetShaderProgram());

	glm::mat4 model = transform.GetWorldMatrix();
	glm::mat4 view = cam.GetViewMatrix();
	glm::mat4 projection = cam.GetProjectionMatrix();

	m_Shader->SetUniform("model", model);
	m_Shader->SetUniform("view", view);
	m_Shader->SetUniform("projection", projection);
	m_Shader->SetUniform("uEyePosition", cam.GetPosition());
	m_Shader->SetUniform("uColor", { 1., 1., 1. });
	m_Shader->SetUniform("uCool", { 0., 0., .55 });
	m_Shader->SetUniform("uWarm", { .3, .3, 0. });


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