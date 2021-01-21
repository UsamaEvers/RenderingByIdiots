#include "../inc/ParticleGenerator.h"
#include "../inc/stb_image.h"
#include <algorithm>
#include <tuple>
ParticleGenerator::ParticleGenerator()
{
	Init();
}

ParticleGenerator::~ParticleGenerator()
{
}

bool ParticleGenerator::Init()
{
	
	VertexPosTex particle_quad[] =
	{
	{{-0.5f, -0.5f, -0.5f,}, { 0.0f, 0.0f }}, //0
	{{ 0.5f, -0.5f, -0.5f,}, { 1.0f, 0.0f }}, //1
	{{ 0.5f,  0.5f, -0.5f,}, { 1.0f, 1.0f }}, //2
	{{-0.5f,  0.5f, -0.5f,}, { 0.0f, 1.0f }}, //3
	};

	unsigned int normalArray[] = {
		0 ,	2,	1,
		2,	0,	3,
	};
	GLuint EBO, VBO = 0;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//bind vao
	glBindVertexArray(VAO);

	//bind vbo 
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_STATIC_DRAW);

	//bind ebo
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(normalArray), normalArray, GL_STATIC_DRAW);

	//bind vbo and ebo to vao
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPosTex), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPosTex), (float*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	std::string crylaugh = "Resources/CRYLAUGH.png";
	std::string sans = "Resources/Sans.png";
	std::string CREEPER = "Resources/creeperColored.png";

	assert(GenTexture(texture1, crylaugh, true));
	assert(GenTexture(texture2, sans, true));
	assert(GenTexture(texture3, CREEPER, false));
	glBindVertexArray(0);

	// create "amount" of particles
	for (unsigned int i = 0; i < amount; ++i)
		this->particles.push_back(Particle());
	return false;
}
glm::vec4 lerp(glm::vec4 v0, glm::vec4 v1, float t) {
	return v0 + t * (v1 - v0);
}
bool ParticleGenerator::Draw(glm::mat4 proj, glm::mat4 view, GLuint shaderProgram)
{
	// use additive blending to give it a 'glow' effect
	glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glBindVertexArray(VAO);
	
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(proj));

	glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
	glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1);
	glUniform1i(glGetUniformLocation(shaderProgram, "texture3"), 2);

	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, texture3);

	std::sort(particles.begin(), particles.end(), [view](const Particle& first, const Particle& last)
		{
			float firstZ = (view * glm::vec4(first.Position, 1.0f)).z;
			float notfirstZ = (view * glm::vec4(last.Position, 1.0f)).z;

			return firstZ < notfirstZ;
		});

	for (Particle particle : this->particles)
	{
		if (particle.Life > 0.0f)
		{			
			glm::mat4 model = glm::translate(glm::mat4(1.0f), particle.Position);
			glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
			glm::vec4 color	= lerp(particle.ColorEnd, particle.ColorBegin, particle.LifeRemaining / particle.Life);
			glUniform4fv(glGetUniformLocation(shaderProgram, "color"), 1, &color[0]);

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
	particle.Position = glm::vec3(0,0,0) + glm::vec3(((rand() % 100) - 50) / 10.0f, ((rand() % 100) - 50) / 10.0f, ((rand() % 100) - 50) / 10.0f) + offset;
	particle.ColorBegin = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	particle.ColorEnd = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f); 
	particle.LifeRemaining = particle.Life = (rand() % 3) + 0.75f;;
}


bool ParticleGenerator::GenTexture(GLuint& texture, std::string textName, bool alphaEnable)
{
	if (!alphaEnable)
	{
		glGenBuffers(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		stbi_set_flip_vertically_on_load(true);

		int width, height, nrChannels;
		unsigned char* data = stbi_load(textName.c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
			return false;
		}
		stbi_image_free(data);
	}
	else
	{


		// texture 2
	   // ---------

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// load image, create texture and generate mipmaps
		stbi_set_flip_vertically_on_load(true);

		int width, height, nrChannels;
		unsigned char* data = stbi_load(textName.c_str(), &width, &height, &nrChannels, 0);

		if (data)
		{
			// note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
			return false;
		}
		//SAY GAY IF YOU THINK MY MIC IS STUPID
		//AND THAT i SHOULD NEVER JOIN CALLS AGAIN!
		stbi_set_flip_vertically_on_load(false);

	}
	return true;
}
