#include "../inc/Mesh.h"
#include "../inc/stb_image.h"

Mesh::Mesh()
{

	VertexPosColTex Vertex[] = {
	{{-0.5f, -0.5f, -0.5f,}, { 1., 0., 0. }, { 0.0f, 0.0f }}, //0
	{{ 0.5f, -0.5f, -0.5f,}, { 1., 0., 0. }, { 1.0f, 0.0f }}, //1
	{{ 0.5f,  0.5f, -0.5f,}, { 1., 0., 0. }, { 1.0f, 1.0f }}, //2
	{{-0.5f,  0.5f, -0.5f,}, { 1., 0., 0. }, { 0.0f, 1.0f }}, //3

	{{-0.5f, -0.5f,  0.5f,}, { 1., 0., 0. }, { 0.0f, 0.0f }}, //4
	{{ 0.5f, -0.5f,  0.5f,}, { 1., 0., 0. }, { 1.0f, 0.0f }}, //5
	{{ 0.5f,  0.5f,  0.5f,}, { 1., 0., 0. }, { 1.0f, 1.0f }}, //6
	{{-0.5f,  0.5f,  0.5f,}, { 1., 0., 0. }, { 0.0f, 1.0f }}, //7

	};

	unsigned int normalArray[] = {  // note that we start from 0!
	0 ,	1,	2,
	2,	3,	0,

	4,	6,	5,
	6,	4,	7,

	0,  3,  4,
	4,  3,  7,

	1,  5,  2,
	5,  6,  2,

	1,  0,  5,
	5,  0,  4,

	2,  6,  3,
	6,  7,  3
	};
	GLuint EBO, VBO = 0;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex), Vertex, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(normalArray), normalArray, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPosColTex), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPosColTex), (float*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPosColTex), (float*)(6 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	
	std::string Container = "Resources/container.jpg";
	std::string CryLaugh = "Resources/Sans.jpg";
	texture1 = TextureManager::CheckIfTextureExists(Container, false);
	texture2 = TextureManager::CheckIfTextureExists(CryLaugh, false);

   	glBindVertexArray(0);
}

Mesh::~Mesh()
{
}



bool Mesh::Draw(glm::mat4 viewmat, glm::mat4 projmat,GLuint shaderProgram, GLFWwindow* window)
{

	glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
	};


	glBindVertexArray(VAO);

	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(viewmat));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projmat));
	glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
	glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);

	for (unsigned int i = 0; i < 10; i++)
	{
		float angle = 20.0f * i;

		glm::mat4 model = glm::translate(glm::mat4(1.0f), cubePositions[i]);
		model = glm::rotate(model, glm::radians(0.0f + i * 10), glm::vec3(1.0f, 0.3f, 0.5f));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}

	glBindVertexArray(0);
	return true;
}
