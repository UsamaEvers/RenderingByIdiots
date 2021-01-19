#include "../inc/Camera.h"

bool Camera::Init()
{

	projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	view = view = glm::lookAt(m_Position, cameraDirection, cameraUp);
	return false;
}
