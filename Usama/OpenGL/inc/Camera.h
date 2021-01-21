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

class Camera
{
private:

	


public:
	Camera(glm::vec3 eyePos) {
		m_Position = eyePos;
	}
	Camera() {}
	~Camera();
	glm::vec2 PitchYaw = glm::vec2(0.0f, -90.f);
	glm::vec3 m_Direction = glm::vec3(0, 0, 0);
	glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::mat4 m_Projection = glm::mat4(1.0f);
	glm::mat4 m_View = glm::mat4(1.0f);
	bool Update(float deltaTime);
};

