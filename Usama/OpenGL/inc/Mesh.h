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

struct VertexPosColTex
{
	glm::vec3 pos;
	glm::vec3 col;
	glm::vec2 tex;
};
struct VertexPosTex
{
	glm::vec3 Pos;
	glm::vec2 tex;
};
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
};

class Mesh
{
private:

protected:
	std::vector<GLuint> textures;
	std::vector<MeshBuffers> allMeshes;
	bool BindTextures(MeshBuffers& mesh, GLuint shaderProgram);

public:
	Mesh();
	~Mesh();
	
	bool CreateCube();
	bool CreateQuad();
	virtual bool Draw(glm::mat4 viewmat, glm::mat4 projmat, GLuint shaderProgram);
};
