#include "Transform.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Transform::Transform() 
	: m_Position(0.)
	, m_Rotation(0.)
	, m_Scale(1.)
{
}

Transform::Transform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl)
	: m_Position(pos)
	, m_Rotation(rot)
	, m_Scale(scl)
{
}

glm::mat4 Transform::GetWorldMatrix()
{
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), m_Scale);

	glm::mat4 rotation = GetRotationMatrix();

	glm::mat4 translation = glm::translate(glm::mat4(1.0f), m_Position);

    return translation * rotation * scale ;
}

glm::mat4 Transform::GetRotationMatrix()
{
	glm::mat4 rotationX = glm::rotate(glm::mat4(1.0f), m_Rotation.x, glm::vec3(1., 0., 0.));
	glm::mat4 rotationY = glm::rotate(glm::mat4(1.0f), m_Rotation.y, glm::vec3(0., 1., 0.));
	glm::mat4 rotationZ = glm::rotate(glm::mat4(1.0f), m_Rotation.z, glm::vec3(0., 0., 1.));
	return rotationY * rotationX * rotationZ;
}
