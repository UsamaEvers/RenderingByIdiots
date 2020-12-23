#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include "../inc/stb_image.h"
#include "../inc/Mesh.h"
#include "../inc/Shader.h"


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
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (glewInit() != GLEW_OK)
		std::cout << "Glew init was not equal to GLEW_OK" << std::endl;

	Mesh mesh;
	glEnable(GL_DEPTH_TEST);
	Shader shader("Shaders/SimpleShader.vert", "Shaders/SimpleShader.frag");
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
			
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//DRAWS A FUNNY FACE =D=D=D=D=D==D=D==D=D=D killme
		mesh.Draw(shader.getID(), window);

			
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}