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
#include "../inc/Texture.h"

struct VertexPosColTex
{
	glm::vec3 pos;
	glm::vec3 col;
	glm::vec2 tex;
};
class Mesh
{
private:
	GLuint VAO,texture1, texture2 = 0;
	float deltaTime = 0.0f;	// Time between current frame and last frame
	float lastFrame = 0.0f; // Time of last frame



public:
	Mesh();
	~Mesh();
	bool Draw(GLuint,GLFWwindow* window);
	bool Draw(glm::mat4 viewmat, glm::mat4 projmat, GLuint shaderProgram, GLFWwindow* window);
	
};

