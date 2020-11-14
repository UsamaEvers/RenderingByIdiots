#pragma once
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class Transform
{
public:

	Transform();
	Transform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl);

	~Transform() {};

	glm::mat4 GetWorldMatrix();
	glm::mat4 GetRotationMatrix();

	glm::vec3& GetPosition() { return m_Position; }
	glm::vec3& GetRotation() { return m_Rotation; }
	glm::vec3& GetScale   () { return m_Scale   ; }


private:
	glm::vec3 m_Position;
	glm::vec3 m_Rotation;
	glm::vec3 m_Scale;
};

