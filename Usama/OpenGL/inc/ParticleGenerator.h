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


struct Particle {
	glm::vec3 Position;
	glm::vec4 ColorBegin;
	glm::vec4 ColorEnd;

	float     Life;
	float	  LifeRemaining;

};
struct VertexPosTex
{
	glm::vec3 Pos;
	glm::vec2 tex;
};
class ParticleGenerator 
{
private:
	GLuint VAO, texture1, texture2, texture3;
	int amount = 1000;
	std::vector<Particle> particles;
	unsigned int lastUsedParticle = 0;
public:
	ParticleGenerator();
	~ParticleGenerator();
	bool Init();
	bool Draw(glm::mat4 proj, glm::mat4 view, GLuint shaderProgram, glm::vec3);
	bool Draw(glm::mat4 proj, glm::mat4 view, GLuint shaderProgram);
	bool Update(float dt, unsigned int newParticles, glm::vec3 offset);
	bool GenTexture(GLuint& texture, std::string textName, bool alphaEnable);
	int firstUnusedParticle();
	void respawnParticle(Particle& particle, glm::vec3 offset);

};		 
