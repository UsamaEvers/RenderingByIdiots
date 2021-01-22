#include "../inc/Mesh.h"
#include "../inc/stb_image.h"
#include "../inc/Texture.h"


Mesh::Mesh()
{

}

Mesh::~Mesh()
{
}


bool Mesh::Draw(glm::mat4 viewmat, glm::mat4 projmat, GLuint shaderProgram)
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

	//	for (auto i : Allobjects)
	//	{
	//		primitiveObjects.at(i);
	//	}
	//
	//	ObjectName objname= CUBE;
	//	switch (objname)
	//	{
	//	case ObjectName::CUBE:
	//		glBindVertexArray(primitiveObjects.at(ObjectName::CUBE).VAO);
	//		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(viewmat));
	//		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projmat));
	//		glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
	//		glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1);
	//		glActiveTexture(GL_TEXTURE0);
	//		glBindTexture(GL_TEXTURE_2D, textures.at(0));
	//		glActiveTexture(GL_TEXTURE1);
	//		glBindTexture(GL_TEXTURE_2D, textures.at(1));
	//
	//		for (unsigned int i = 0; i < 10; i++)
	//		{
	//			float angle = 20.0f * i;
	//
	//			glm::mat4 model = glm::translate(glm::mat4(1.0f), cubePositions[i]);
	//			model = glm::rotate(model, glm::radians(0.0f + i * 10), glm::vec3(1.0f, 0.3f, 0.5f));
	//			glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
	//			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//		}
	//		glBindVertexArray(0);
	//		break;
	//
	//	case ObjectName::QUAD:
	//			break;
	//	
	//	default:
	//		break;
	//	}
	//	

	for (MeshBuffers mesh : allMeshes)
	{
		glBindVertexArray(mesh.VAO);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(viewmat));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projmat));

		//	glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
		//	glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1);
		//	glActiveTexture(GL_TEXTURE0);
		//	glBindTexture(GL_TEXTURE_2D, mesh.textures.at(0));
		//	glActiveTexture(GL_TEXTURE1);
		//	glBindTexture(GL_TEXTURE_2D, mesh.textures.at(1));
		BindTextures(mesh, shaderProgram);
		for (unsigned int i = 0; i < 10; i++)
		{
			float angle = 20.0f * i;

			glm::mat4 model = glm::translate(glm::mat4(1.0f), cubePositions[i]);
			model = glm::rotate(model, glm::radians(0.0f + i * 10), glm::vec3(1.0f, 0.3f, 0.5f));
			glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		}

		glBindVertexArray(0);
	}
	return true;
}

bool Mesh::CreateCube()
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
	MeshBuffers mb;
	mb.meshname = CUBE;
	glGenVertexArrays(1, &mb.VAO);
	glGenBuffers(1, &mb.EBO);
	glGenBuffers(1, &mb.VBO);
	glBindVertexArray(mb.VAO);

	glBindBuffer(GL_ARRAY_BUFFER, mb.VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex), Vertex, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mb.EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(normalArray), normalArray, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPosColTex), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPosColTex), (float*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPosColTex), (float*)(6 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	std::string Container = "Resources/container.jpg";
	std::string CryLaugh = "Resources/Sans.jpg";
	mb.textures.push_back(TextureManager::CheckIfTextureExists(Container, false));
	mb.textures.push_back(TextureManager::CheckIfTextureExists(CryLaugh, false));
	mb.totalTextures = 2;
	glBindVertexArray(0);
	allMeshes.push_back(mb);
	return true;
}

bool Mesh::CreateQuad()
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

	MeshBuffers mb;
	mb.meshname = QUAD;
	glGenVertexArrays(1, &mb.VAO);
	glGenBuffers(1, &mb.VBO);
	glGenBuffers(1, &mb.EBO);

	//bind vao
	glBindVertexArray(mb.VAO);

	//bind vbo 
	glBindBuffer(GL_ARRAY_BUFFER, mb.VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_STATIC_DRAW);

	//bind ebo
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mb.EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(normalArray), normalArray, GL_STATIC_DRAW);

	//bind vbo and ebo to vao
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPosTex), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPosTex), (float*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	std::string crylaugh = "Resources/CRYLAUGH.png";
	std::string sans = "Resources/Sans.png";
	std::string CREEPER = "Resources/creeperColored.png";

	mb.textures.push_back(TextureManager::CheckIfTextureExists(crylaugh, true));
	mb.textures.push_back(TextureManager::CheckIfTextureExists(sans, true));
	mb.textures.push_back(TextureManager::CheckIfTextureExists(CREEPER, false));
	mb.totalTextures = 3;
	allMeshes.push_back(mb);
	return false;
}

bool Mesh::BindTextures(MeshBuffers& mesh, GLuint shaderProgram)
{
	int total = mesh.totalTextures;
	for (int i = 0; i < total; i++)
	{
		if (i == 4)
		{
			return false;
		}
		if (i == 3)
			glUniform1i(glGetUniformLocation(shaderProgram, "texture4"), i);
		if (i == 2)
			glUniform1i(glGetUniformLocation(shaderProgram, "texture3"), i);
		if (i == 1)
			glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), i);
		if (i == 0)
			glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), i);
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, mesh.textures.at(i));
	}

	return true;
}