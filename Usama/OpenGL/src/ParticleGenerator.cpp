#include "../inc/ParticleGenerator.h"
#include "../inc/stb_image.h"
#include <algorithm>
#include <tuple>
#include "../inc/Texture.h"
#include "../inc/Shader.h"
ParticleGenerator::ParticleGenerator()
{
	Init();
}

ParticleGenerator::~ParticleGenerator()
{
}

bool ParticleGenerator::Init()
{
	CreateQuad(3, PARTICLESHADER);
	for (unsigned int i = 0; i < amount; ++i)
		this->particles.push_back(Particle());
	return false;
}
glm::vec4 lerp(glm::vec4 v0, glm::vec4 v1, float t) {
	return v0 + t * (v1 - v0);
}
bool ParticleGenerator::Draw(glm::mat4 proj, glm::mat4 view, GLuint shaderProgram)
{
	glEnable(GL_BLEND);
	std::sort(particles.begin(), particles.end(), [view](const Particle& first, const Particle& last)
		{
			float firstZ = (view * glm::vec4(first.Position, 1.0f)).z;
			float notfirstZ = (view * glm::vec4(last.Position, 1.0f)).z;

			return firstZ < notfirstZ;
		});
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glUseProgram(ShaderManager::GetShaderID(PARTICLESHADER));

	glBindVertexArray(allMeshes.at(0).VAO);
	glUniformMatrix4fv(ShaderManager::GetShaderLocations(PARTICLESHADER).WhichType.at(VIEW), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(ShaderManager::GetShaderLocations(PARTICLESHADER).WhichType.at(PROJ), 1, GL_FALSE, glm::value_ptr(proj));
	BindTextures(allMeshes.at(0), shaderProgram);

	for (Particle particle : this->particles)
	{
		if (particle.Life > 0.0f)
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), particle.Position);
			glUniformMatrix4fv(ShaderManager::GetShaderLocations(PARTICLESHADER).WhichType.at(MODEL), 1, GL_FALSE, glm::value_ptr(model));
			glm::vec4 color = lerp(particle.ColorEnd, particle.ColorBegin, particle.LifeRemaining / particle.Life);
			glUniform4fv(ShaderManager::GetShaderLocations(PARTICLESHADER).WhichType.at(COLOR), 1, &color[0]);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		}
	}
	glBindVertexArray(0);

	// don't forget to reset to default blending mode
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_BLEND);
	return true;
}

bool ParticleGenerator::Update(float dt, unsigned int newParticles, glm::vec3 offset)
{
	glm::vec3 positionReduction = glm::vec3(0, 1, 0);
	// add new particles 
	for (unsigned int i = 0; i < newParticles; ++i)
	{
		int unusedParticle = this->firstUnusedParticle();
		if (unusedParticle != -1)
		{
			this->respawnParticle(this->particles[unusedParticle], offset);
		}
	}
	// update all particles
	for (unsigned int i = 0; i < this->amount; ++i)
	{
		Particle& p = this->particles[i];
		p.LifeRemaining -= dt; // reduce life
		p.Position -= glm::vec3(0, 0.5f * dt, 0.0f);
	}

	return true;
}

int ParticleGenerator::firstUnusedParticle()
{
	// first search from last used particle, this will usually return almost instantly
	for (unsigned int i = lastUsedParticle; i < this->amount; ++i) {
		if (this->particles[i].LifeRemaining <= 0.0f) {
			lastUsedParticle = i;
			return i;
		}
	}
	// otherwise, do a linear search
	for (unsigned int i = 0; i < lastUsedParticle; ++i) {
		if (this->particles[i].LifeRemaining <= 0.0f) {
			lastUsedParticle = i;
			return i;
		}
	}
	// all particles are taken, override the first one (note that if it repeatedly hits this case, more particles should be reserved)
	return -1;
}

void ParticleGenerator::respawnParticle(Particle& particle, glm::vec3 offset)
{
	float random = ((rand() % 100) - 50) / 10.0f;
	particle.Position = glm::vec3(0, 0, 0) + glm::vec3(((rand() % 100) - 50) / 10.0f, ((rand() % 100) - 50) / 10.0f, ((rand() % 100) - 50) / 10.0f) + offset;
	particle.ColorBegin = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	particle.ColorEnd = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);
	particle.LifeRemaining = particle.Life = (rand() % 3) + 0.75f;;
}

