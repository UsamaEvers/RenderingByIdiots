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
#include "Mesh.h"

struct Particle {
	glm::vec3 Position;
	glm::vec4 ColorBegin;
	glm::vec4 ColorEnd;

	float     Life;
	float	  LifeRemaining;

};

class ParticleGenerator :  public Mesh
{
private:
	int amount = 1000;
	std::vector<Particle> particles;
	unsigned int lastUsedParticle = 0;
public:
	ParticleGenerator();
	~ParticleGenerator();
	bool Init();
	bool Draw(glm::mat4 proj, glm::mat4 view, GLuint shaderProgram);
	bool Update(float dt, unsigned int newParticles, glm::vec3 offset);
	int firstUnusedParticle();
	void respawnParticle(Particle& particle, glm::vec3 offset);

};		 
