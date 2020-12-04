#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include "../inc/stb_image.h"

struct Vertex
{
	glm::vec3 pos;
	glm::vec3 color;

};
struct VertexPosTex
{
	glm::vec3 pos;
	glm::vec2 tex;
};
struct VertexPosColTex
{
	glm::vec3 pos;
	glm::vec3 col;
	glm::vec2 tex;
};
int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(400, 300, "Usama OpenGL Project", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		std::cout << "Glew init was not equal to GLEW_OK" << std::endl;


	// load mesh

	
	Vertex Plane[] = {
		{{ 0.5f,  0.5f, 0.0f}, {1., 0., 0.}},
		{{ 0.5f, -0.5f, 0.0f}, {0., 1., 0.}},
		{{-0.5f, -0.5f, 0.0f}, {0., 0., 1.}},
		{{-0.5f,  0.5f, 0.0f}, {1., 0., 0.}},
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};
	VertexPosTex Dorito[] = {
	{{ 0.5f,  0.5f, 0.0f}, {0., 0., }},
	{{ 0.5f, -0.5f, 0.0f}, {1., 0., }},
	{{-0.5f, -0.5f, 0.0f}, {0.5, 1., }},
	};

	VertexPosColTex VertexWithTexture[] = {

		{{  0.5f,  0.5f, 0.0f, }, { 1., 0., 0. }, {  2.0f, 2.0f} },    // top right
		{{  0.5f, -0.5f, 0.0f, }, { 0., 1., 0. }, {  2.0f, 0.0f} },    // bottom right
		{{ -0.5f, -0.5f, 0.0f, }, { 0., 0., 1. }, {  0.0f, 0.0f} },   // bottom left
		{{ -0.5f,  0.5f, 0.0f, }, { 1., 1., 0. }, {  0.0f, 2.0f} },  // top left 
	};
	//unsigned int indicesDorito[] = {  // note that we start from 0!
	//0, 1, 3,   // first triangle
	//};
	unsigned int VBO;
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexWithTexture), VertexWithTexture, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	unsigned int texture1, texture2;
	glGenBuffers(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = stbi_load("yes/container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	// texture 2
   // ---------
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	stbi_set_flip_vertically_on_load(true);

	data = stbi_load("yes/CRYLAUGH.png", &width, &height, &nrChannels, 0);

	if (data)
	{
		// note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	//SAY GAY IF YOU THINK MY MIC IS STUPID
	//AND THAT i SHOULD NEVER JOIN CALLS AGAIN!




	// load shader
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec3 aUV;\n"
		"layout (location = 2) in vec2 aTC; \n"
		"out vec3 uv;\n"
		"out vec2 TC;"
		//"uniform float addToPosition;\n"
		"void main()\n"
		"{\n"
		"	uv = aUV;\n"
		"   gl_Position = vec4(aPos, 1.0);\n"
		"	TC = aTC;\n"
		"}\0";

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	{
		int  success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
	}

	const char* fragmentShaderSource = "#version 330 core\n"
		"in vec3 uv;\n"
		"in vec2 TC;\n"
		"out vec4 FragColor;\n"
		"uniform sampler2D texture1;\n"
		"uniform sampler2D texture2;\n"
		"void main()\n"
		"{\n"
		"	FragColor = mix(texture(texture1, TC),texture(texture2, TC),0.2);//* vec4(uv, 1.0); \n"
		"}\0";

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	{
		int  success;
		char infoLog[512];
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
	}


	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	float addtoposition = 0.0f;

	//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glUseProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPosColTex), 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPosColTex), (float*)(3 * sizeof(float)));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPosColTex), (float*)(6 * sizeof(float)));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);	
		glEnableVertexAttribArray(2);
		glUseProgram(shaderProgram);

		glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
		glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1);

		//int vertexColorLocation = glGetUniformLocation(shaderProgram, "addToPosition");
		//glUniform1f(vertexColorLocation, addtoposition);

		glUseProgram(shaderProgram);	
		glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	
		addtoposition += 0.0001f;
		
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}