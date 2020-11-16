#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../Mesh.h"
#include "../Camera.h"

#include <iostream>
#include <vector>
#include "../Loaders.h"

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	int WIDTH = 1920;
	int HEIGHT = 1080;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) 
		std::cout << "Glew init was not equal to GLEW_OK" << std::endl;

	Camera camera(WIDTH, HEIGHT, 90.0f, 0.01f, 1000.0f);

	Mesh mesh(Loaders::LoadModel("dragon.obj"));

	//camera.GetTransform().GetPosition().z =  -5.0f;
	mesh.GetTransform().GetScale() *= 1.0f;
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	//glFrontFace(GL_CW);

	glClearColor(0.3f, 0.2f, 0.8f, 1.f);

	int present = glfwJoystickPresent(GLFW_JOYSTICK_1);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// joystick
		
		if (1 == present)
		{
			int axisCount;
			const float* axis = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axisCount);
			
			camera.GetTransform().GetRotation().y += -(static_cast<int>(axis[2] * 10) / 10.0f) * 0.1;
			camera.GetTransform().GetRotation().x += -(static_cast<int>(axis[3] * 10) / 10.0f) * 0.1;

			glm::vec4 vel((static_cast<int>(axis[0] * 10) / 10.0f), 0., (static_cast<int>(axis[1] * 10) / 10.0f), 0.);
			vel *= 0.1f;

			camera.GetTransform().GetPosition() += glm::vec3(vel * glm::inverse(camera.GetTransform().GetRotationMatrix()));
			
		}

		mesh.GetTransform().GetPosition().z = 0.0f;

		for (int i = 0; i < 10; i++)
		{
			mesh.GetTransform().GetPosition().z = -i*5.f;
			mesh.Render(camera);
		}
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	Shader::ClearShaders();
	glfwTerminate();
	return 0;
}
