#pragma once
#include "Component.h"

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class Camera : public Component
{
public:
	static std::string GetName() { return "Camera"; };

	Camera();
	Camera(int width, int height, float fov, float near, float far);
	~Camera() {}

	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();

	glm::vec3 GetPosition();

private:

	float m_AspectRatio;
	float m_Fov;
	float m_Near;
	float m_Far;

};

