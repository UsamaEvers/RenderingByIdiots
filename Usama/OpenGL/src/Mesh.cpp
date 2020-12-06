#include "../inc/Mesh.h"
#include "../inc/stb_image.h"

Mesh::Mesh()
{
	
	unsigned int normalArray[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	VertexPosColTex Vertex[] = {

		{{  0.5f,  0.5f, 0.0f, }, { 1., 0., 0. }, {  2.0f, 2.0f} },    // top right
		{{  0.5f, -0.5f, 0.0f, }, { 0., 1., 0. }, {  2.0f, 0.0f} },    // bottom right
		{{ -0.5f, -0.5f, 0.0f, }, { 0., 0., 1. }, {  0.0f, 0.0f} },   // bottom left
		{{ -0.5f,  0.5f, 0.0f, }, { 1., 1., 0. }, {  0.0f, 2.0f} },  // top left 
	};
	glGenBuffers(1, &EBO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex), Vertex, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(normalArray), normalArray, GL_STATIC_DRAW);
	std::string Container = "yes/container.jpg";
	std::string CryLaugh = "yes/CRYLAUGH.png";
	assert(GenTexture(texture1, Container, false));
	assert(GenTexture(texture2, CryLaugh, true));
}

Mesh::~Mesh()
{
}
bool Mesh::Draw(GLuint shaderProgram)
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO);// mesh.GetVBO());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); //mesh.GetEBO());
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPosColTex), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPosColTex), (float*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPosColTex), (float*)(6 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
	glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1);


	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	return true;
}
bool Mesh::GenTexture(GLuint& texture, std::string textName, bool alphaEnable)
{
	if (!alphaEnable)
	{
		glGenBuffers(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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
