#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include "Transform.h"

class Camera
{
public:

	Camera();
	Camera(int width, int height, float fov, float near, float far);
	~Camera() {}

	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();

	Transform& GetTransform() { return m_Transform; };

private:

	float m_AspectRatio;
	float m_Fov;
	float m_Near;
	float m_Far;

	Transform m_Transform;
};

