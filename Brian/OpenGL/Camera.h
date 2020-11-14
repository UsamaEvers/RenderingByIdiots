#pragma once
#include "Transform.h"

class Camera
{
public:

	Camera();
	Camera(int width, int height, float fov, float near, float far);
	~Camera() {}

	Transform& GetTransform() { return m_Transform; }

	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();

private:

	float m_AspectRatio;
	float m_Fov;
	float m_Near;
	float m_Far;

	Transform m_Transform;

};

