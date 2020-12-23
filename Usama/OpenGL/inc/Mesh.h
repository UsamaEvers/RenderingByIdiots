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
class Mesh
{
private:
	GLuint EBO, VBO, texture1, texture2 = 0;
	float deltaTime = 0.0f;	// Time between current frame and last frame
	float lastFrame = 0.0f; // Time of last frame
	bool firstMouse;
	float lastX, lastY;
	float yaw = -90.f;
	float pitch = 0;;
public:
	Mesh();
	~Mesh();
	void processInput(GLFWwindow* window);
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	bool Draw(GLuint,GLFWwindow* window);
	bool GenTexture(GLuint& texture, std::string textName, bool alphaEnable);
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

	glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
	glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
};

