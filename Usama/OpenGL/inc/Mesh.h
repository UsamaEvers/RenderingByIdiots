#pragma once
#include <GL/glew.h>
#include <iostream>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <vector>
struct VertexPosColTex
{
	glm::vec3 pos;
	glm::vec3 col;
	glm::vec2 tex;
};
class Mesh
{
private:
	GLuint EBO, VBO, texture1, texture2 = 0;
public:
	Mesh();
	~Mesh();
	GLuint GetEBO() { return EBO; }
	GLuint GetVBO() { return VBO; }
	bool Draw(GLuint);
	bool GenTexture(GLuint& texture, std::string textName, bool alphaEnable);

};

