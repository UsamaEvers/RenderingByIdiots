#include "Camera.h"

#include "Entity.h"
#include "Transform.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera()
	: Component(GetName())
	, m_AspectRatio(16.0f/9.0f)
	, m_Fov(90.0f)
	, m_Near(0.01f)
	, m_Far(1000.0f)
{
}

Camera::Camera(int width, int height, float fov, float near, float far)
	: Component(GetName())
	, m_AspectRatio(static_cast<float>(width)/static_cast<float>(height))
	, m_Fov(fov)
	, m_Near(near)
	, m_Far(far)
{
}

glm::mat4 Camera::GetViewMatrix()
{
	Transform& transform = GetParent()->GetComponent<Transform>();

    return glm::inverse(transform.GetWorldMatrix());
}

glm::mat4 Camera::GetProjectionMatrix()
{
	return glm::perspective(glm::radians(m_Fov), m_AspectRatio, m_Near, m_Far);
}

glm::vec3 Camera::GetPosition()
{
	Transform& transform = GetParent()->GetComponent<Transform>();
	return transform.GetPosition();
}
