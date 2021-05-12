#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <vector>
#include <GLFW/glfw3.h>
#include "Shader.h"

struct VertexPosColTex
{
	glm::vec3 pos;
	glm::vec3 col;
	glm::vec2 tex;
};
struct VertexPosTexNor
{
	glm::vec3 pos;
	glm::vec2 tex;
	glm::vec3 Nor;
};
struct VertexPosTex
{
	glm::vec3 Pos;
	glm::vec2 tex;
};
struct VertexPosNor
{
	glm::vec3 pos;
	glm::vec3 Nor;
};

//struct VertexPos
//{
//	glm::vec3 pos;
//};

enum MeshName
{
	CUBE,
	QUAD
};
struct MeshBuffers
{
	MeshName meshname;
	GLuint VAO, VBO, EBO, totalTextures = 0;
	std::vector<GLuint> textures;
	e_ShaderType Shadertype;
};

class Mesh
{
private:

protected:
	std::vector<GLuint> textures;

public:
	Mesh();
	~Mesh();
	std::vector<MeshBuffers> allMeshes;
	bool BindTextures(MeshBuffers& mesh, GLuint shaderProgram);
	bool CreateCube(bool lit);
	bool CreateCube();
	bool CreateQuad();
	bool CreateQuad(int amountOfTextures, e_ShaderType shadertype);
	virtual bool Draw(glm::mat4 viewmat, glm::mat4 projmat, GLuint shaderProgram, glm::vec3 cameraPos);
};
