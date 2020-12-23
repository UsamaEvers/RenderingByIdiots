#include "../inc/Mesh.h"
#include "../inc/stb_image.h"

Mesh::Mesh()
{

	//	unsigned int normalArray[] = {  // note that we start from 0!
	//		0, 1, 3,   // first triangle
	//		1, 2, 3    // second triangle
	//	};
//	VertexPosColTex Vertexa[] = {
//
//		{{  0.5f,  0.5f, 0.0f, }, { 1., 0., 0. }, {  2.0f, 2.0f} },    // top right
//		{{  0.5f, -0.5f, 0.0f, }, { 0., 1., 0. }, {  2.0f, 0.0f} },    // bottom right
//		{{ -0.5f, -0.5f, 0.0f, }, { 0., 0., 1. }, {  0.0f, 0.0f} },   // bottom left
//		{{ -0.5f,  0.5f, 0.0f, }, { 1., 1., 0. }, {  0.0f, 2.0f} },  // top left 
//	};
	//VertexPosColTex Vertex[] = {
	//{{-0.5f, -0.5f, -0.5f,}, { 1., 0., 0. }, { 0.0f, 0.0f }}, //0
	//{{ 0.5f, -0.5f, -0.5f,}, { 1., 0., 0. }, { 1.0f, 0.0f }}, //1
	//{{ 0.5f,  0.5f, -0.5f,}, { 1., 0., 0. }, { 1.0f, 1.0f }}, //2
	//{{ 0.5f,  0.5f, -0.5f,}, { 1., 0., 0. }, { 1.0f, 1.0f }}, //2
	//{{-0.5f,  0.5f, -0.5f,}, { 1., 0., 0. }, { 0.0f, 1.0f }}, //3
	//{{-0.5f, -0.5f, -0.5f,}, { 1., 0., 0. }, { 0.0f, 0.0f }}, //0
	//											 
	//{{-0.5f, -0.5f,  0.5f,}, { 1., 0., 0. }, { 0.0f, 0.0f }}, //4
	//{{ 0.5f, -0.5f,  0.5f,}, { 1., 0., 0. }, { 1.0f, 0.0f }}, //5
	//{{ 0.5f,  0.5f,  0.5f,}, { 1., 0., 0. }, { 1.0f, 1.0f }}, //6
	//{{ 0.5f,  0.5f,  0.5f,}, { 1., 0., 0. }, { 1.0f, 1.0f }}, //6
	//{{-0.5f,  0.5f,  0.5f,}, { 1., 0., 0. }, { 0.0f, 1.0f }}, //7
	//{{-0.5f, -0.5f,  0.5f,}, { 1., 0., 0. }, { 0.0f, 0.0f }}, //4
	//											 
	//{{-0.5f,  0.5f,  0.5f,}, { 1., 0., 0. }, { 1.0f, 0.0f }}, //8
	//{{-0.5f,  0.5f, -0.5f,}, { 1., 0., 0. }, { 1.0f, 1.0f }}, //9
	//{{-0.5f, -0.5f, -0.5f,}, { 1., 0., 0. }, { 0.0f, 1.0f }}, //10
	//{{-0.5f, -0.5f, -0.5f,}, { 1., 0., 0. }, { 0.0f, 1.0f }}, //10
	//{{-0.5f, -0.5f,  0.5f,}, { 1., 0., 0. }, { 0.0f, 0.0f }}, //4
	//{{-0.5f,  0.5f,  0.5f,}, { 1., 0., 0. }, { 1.0f, 0.0f }}, //8
	//									 
	//{{ 0.5f,  0.5f,  0.5f,}, { 1., 0., 0. }, { 1.0f, 0.0f }}, //11
	//{{ 0.5f,  0.5f, -0.5f,}, { 1., 0., 0. }, { 1.0f, 1.0f }}, //2
	//{{ 0.5f, -0.5f, -0.5f,}, { 1., 0., 0. }, { 0.0f, 1.0f }}, //12
	//{{ 0.5f, -0.5f, -0.5f,}, { 1., 0., 0. }, { 0.0f, 1.0f }}, //12
	//{{ 0.5f, -0.5f,  0.5f,}, { 1., 0., 0. }, { 0.0f, 0.0f }}, //13
	//{{ 0.5f,  0.5f,  0.5f,}, { 1., 0., 0. }, { 1.0f, 0.0f }}, //11
	//									 
	//{{-0.5f, -0.5f, -0.5f,}, { 1., 0., 0. }, { 0.0f, 1.0f }}, //10
	//{{ 0.5f, -0.5f, -0.5f,}, { 1., 0., 0. }, { 1.0f, 1.0f }}, //14
	//{{ 0.5f, -0.5f,  0.5f,}, { 1., 0., 0. }, { 1.0f, 0.0f }}, //5
	//{{ 0.5f, -0.5f,  0.5f,}, { 1., 0., 0. }, { 1.0f, 0.0f }}, //5
	//{{-0.5f, -0.5f,  0.5f,}, { 1., 0., 0. }, { 0.0f, 0.0f }}, //4
	//{{-0.5f, -0.5f, -0.5f,}, { 1., 0., 0. }, { 0.0f, 1.0f }}, //10
	//						 
	//{{-0.5f,  0.5f, -0.5f,}, { 1., 0., 0. }, { 0.0f, 1.0f }}, //3
	//{{ 0.5f,  0.5f, -0.5f,}, { 1., 0., 0. }, { 1.0f, 1.0f }}, //2
	//{{ 0.5f,  0.5f,  0.5f,}, { 1., 0., 0. }, { 1.0f, 0.0f }}, //11
	//{{ 0.5f,  0.5f,  0.5f,}, { 1., 0., 0. }, { 1.0f, 0.0f }}, //11
	//{{-0.5f,  0.5f,  0.5f,}, { 1., 0., 0. }, { 0.0f, 0.0f }}, //14
	//{{-0.5f,  0.5f, -0.5f,}, { 1., 0., 0. }, { 0.0f, 1.0f }}  //3
	//};					
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

	glGenBuffers(1, &EBO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex), Vertex, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(normalArray), normalArray, GL_STATIC_DRAW);
	std::string Container = "yes/container.jpg";
	std::string CryLaugh = "yes/Sans.jpg";
	assert(GenTexture(texture1, Container, false));
	assert(GenTexture(texture2, CryLaugh, false));
}

Mesh::~Mesh()
{
}
void Mesh::processInput(GLFWwindow* window)
{


	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	float cameraSpeed = 2.5f * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		pitch += 6 * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		pitch += -6 * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		yaw += 6 * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		yaw += -6 *cameraSpeed;


}

void Mesh::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);
}


bool Mesh::Draw(GLuint shaderProgram, GLFWwindow* window)
{

	processInput(window);
	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);
	if (pitch > 0.0f)
		int a;
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

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);


	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	glm::mat4 view;
	view = view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);



	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPosColTex), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPosColTex), (float*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPosColTex), (float*)(6 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	//unsigned int transformLoc = glGetUniformLocation(shaderProgram, "modelmat4");
	//glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(Matrix4));
	//int modelLoc = glGetUniformLocation(shaderProgram, "model");
	//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	int viewlLoc = glGetUniformLocation(shaderProgram, "view");
	glUniformMatrix4fv(viewlLoc, 1, GL_FALSE, glm::value_ptr(view));
	int proj = glGetUniformLocation(shaderProgram, "projection");
	glUniformMatrix4fv(proj, 1, GL_FALSE, glm::value_ptr(projection));


	glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
	glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1);


	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);

	for (unsigned int i = 0; i < 10; i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[i]);
		float angle = 20.0f * i;
		model = glm::rotate(model, glm::radians(0.0f + i * 10), glm::vec3(1.0f, 0.3f, 0.5f));
		int modelLoc = glGetUniformLocation(shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, 36);

	return true;
}
bool Mesh::GenTexture(GLuint& texture, std::string textName, bool alphaEnable)
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
