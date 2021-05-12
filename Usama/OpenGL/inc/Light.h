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
#include "Mesh.h"
struct VertexPos
{
	glm::vec3 pos;
};
struct Buffers
{
	GLuint VAO, VBO, EBO = 0;
};
class Light
{
public:
	Light();
	~Light();
	bool Update(glm::mat4 viewmat, glm::mat4 projmat);
	bool Update();
private:
	bool CreateCube();
	bool Init();
	Buffers lightBuffer;
	glm::vec3 lightPosition;
	std::vector<MeshBuffers> allMeshes;

};


