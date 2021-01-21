#include "../inc/Input.h"




void Input::processInput(GLFWwindow* window, float dt, Camera& TheCamera)
{

	float cameraSpeed = 5.0f * dt;

	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraRight = glm::normalize(glm::cross(up, TheCamera.m_Direction));
	glm::vec3 cameraUp = glm::cross(TheCamera.m_Direction, cameraRight);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		TheCamera.m_Position += cameraSpeed * TheCamera.m_Direction;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		TheCamera.m_Position -= cameraSpeed * TheCamera.m_Direction;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		TheCamera.m_Position -= glm::normalize(glm::cross(TheCamera.m_Direction, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		TheCamera.m_Position += glm::normalize(glm::cross(TheCamera.m_Direction, cameraUp)) * cameraSpeed;
	
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		TheCamera.PitchYaw.x += 6 * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		TheCamera.PitchYaw.x += -6 * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		TheCamera.PitchYaw.y += 6 * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		TheCamera.PitchYaw.y += -6 * cameraSpeed;
}
