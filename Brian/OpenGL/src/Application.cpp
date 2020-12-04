#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../Entity.h"
#include "../Transform.h"
#include "../Mesh.h"
#include "../Camera.h"
#include "../MeshRenderer.h"

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

	Entity camera;
	camera.AddComponent(new Camera(WIDTH, HEIGHT, 90.0f, 0.01f, 1000.0f));

	Mesh* dragonMesh = new Mesh(Loaders::LoadModel("dragon.obj"));
	Mesh* monkeyMesh = new Mesh(Loaders::LoadModel("Monkey.obj"));
	Mesh* bunnyMesh = new Mesh(Loaders::LoadModel("bunny.obj"));
	Entity dragon1;
	dragon1.AddComponent(new MeshRenderer(dragonMesh));
	
	Entity dragon2;
	dragon2.AddComponent(new MeshRenderer(monkeyMesh));
	dragon2.GetComponent<Transform>().GetPosition().z = -10.;
	
	Entity dragon3;
	dragon3.AddComponent(new MeshRenderer(bunnyMesh));
	dragon3.GetComponent<Transform>().GetPosition().x = -10.;

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

			Transform& t = camera.GetComponent<Transform>();
			t.GetRotation().y += -(static_cast<int>(axis[2] * 10) / 10.0f) * 0.1;
			t.GetRotation().x += -(static_cast<int>(axis[3] * 10) / 10.0f) * 0.1;

			glm::vec4 vel((static_cast<int>(axis[0] * 10) / 10.0f), 0., (static_cast<int>(axis[1] * 10) / 10.0f), 0.);
			vel *= 0.1f;

			t.GetPosition() += glm::vec3(vel * glm::inverse(t.GetRotationMatrix()));
			
		}

		dragon2.GetComponent<Transform>().GetRotation().x += 0.01;

		MeshRenderer& m1 = dragon1.GetComponent<MeshRenderer>();
		m1.Render(camera.GetComponent<Camera>());

		MeshRenderer& m2 = dragon2.GetComponent<MeshRenderer>();
		m2.Render(camera.GetComponent<Camera>());

		MeshRenderer& m3 = dragon3.GetComponent<MeshRenderer>();
		m3.Render(camera.GetComponent<Camera>());
		
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	Shader::ClearShaders();
	glfwTerminate();
	return 0;
}
