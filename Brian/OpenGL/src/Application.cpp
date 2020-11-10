#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../Mesh.h"
#include <vector>

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1920, 1080, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	
	if (glewInit() != GLEW_OK)
		std::cout << "Glew init was not equal to GLEW_OK" << std::endl;

	std::vector<Vertex> vertices;
	vertices.push_back({ { 1.,  1, 0.}, {1., 0., 0.} });
	vertices.push_back({ { 1., -1, 0.}, {0., 1., 0.} });
	vertices.push_back({ {-1., -1, 0.}, {0., 0., 1.} });
	vertices.push_back({ {-1.,  1, 0.}, {0., 1., 1.} });
	std::vector<int> indices({ 0, 1, 3, 1, 2, 3 });

	Mesh mesh(vertices, indices);

	

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		mesh.Render();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	Shader::ClearShaders();
	glfwTerminate();
	return 0;
}

// joystick
//int present = glfwJoystickPresent(GLFW_JOYSTICK_1);
//
//if (1 == present)
//{
//	int axisCount;
//	const float* axis = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axisCount);
//	for (int i = 0; i < axisCount; i++)
//	{
//		std::cout << i << ": " << axis[i] << " ";
//	}
//	std::cout << std::endl;
//}
