#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include "../inc/stb_image.h"
#include "../inc/Mesh.h"
#include "../inc/Shader.h"
#include "../inc/ParticleGenerator.h"
#include <time.h>

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(800, 600, "Usama OpenGL Project", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (glewInit() != GLEW_OK)
		std::cout << "Glew init was not equal to GLEW_OK" << std::endl;

	Mesh mesh;
	ParticleGenerator ParticleGenerator;


	Shader shader("Shaders/SimpleShader.vert", "Shaders/SimpleShader.frag");
	Shader shader1("Shaders/ParticleShader.vert", "Shaders/ParticleShader.frag");

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	/* Loop until the user closes the window */
	float elapsedtime = 0;
	float previoustime = 0;

	glClearColor(0.4, 0.6, 0.9, 1.0f);
	while (!glfwWindowShouldClose(window))
	{
			
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		float currenttime = clock();
		elapsedtime =  0.001f*(currenttime- previoustime);
		previoustime = currenttime;
		glUseProgram(shader.getID());
		mesh.Draw(shader.getID(), window);
		glUseProgram(shader1.getID());
		ParticleGenerator.Update(elapsedtime, 3, glm::vec3(0,0,0));
		ParticleGenerator.Draw(mesh.projection, mesh.view, shader1.getID(), mesh.cameraPos);
		

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
		
	}

	glfwTerminate();
	return 0;
}