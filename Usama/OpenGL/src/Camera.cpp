#include "../inc/Camera.h"

Camera::~Camera()
{
}


bool Camera::Update(float deltaTime)
{
	/*glm::vec3 direction;*/
	m_Direction.x = cos(glm::radians(PitchYaw.y)) * cos(glm::radians(PitchYaw.x));
	m_Direction.y = sin(glm::radians(PitchYaw.x));
	m_Direction.z = sin(glm::radians(PitchYaw.y)) * cos(glm::radians(PitchYaw.x));
	m_Direction = glm::normalize(m_Direction);

	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
//	glm::vec3 cameraUp = glm::cross(m_Direction, cameraRight);

	//	m_Position = eyePos;
	m_Projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	glm::vec3 tempa = glm::vec3(-6, 9.5f, -8.0f);
	glm::vec3 tempb = glm::vec3(0.45f, -0.68f, 0.57f);
	glm::vec3 cameraRight = glm::normalize(glm::cross(up, tempb));

	glm::vec3 cameraUp = glm::cross(tempb, cameraRight);

	//m_View = glm::lookAt(m_Position, m_Position + m_Direction, cameraUp);
	m_View = glm::lookAt(tempa, tempb, cameraUp);

	return true;
}
