#include "../inc/Light.h" 
Light::Light()
{
	CreateCube();
}

Light::~Light()
{
}

bool Light::Update(glm::mat4 viewmat, glm::mat4 projmat)
{
	glUseProgram(ShaderManager::GetShaderID(LIGHTCUBESHADER));
	glBindVertexArray(lightBuffer.VAO);
	glUniformMatrix4fv(ShaderManager::GetShaderLocations(LIGHTCUBESHADER).WhichType.at(VIEW), 1, GL_FALSE, glm::value_ptr(viewmat));
	glUniformMatrix4fv(ShaderManager::GetShaderLocations(LIGHTCUBESHADER).WhichType.at(PROJ), 1, GL_FALSE, glm::value_ptr(projmat));
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 5.0f, 0.0f));
	//model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
	glm::vec4 Color = glm::vec4(1.0f);
	glUniform4fv(ShaderManager::GetShaderLocations(LIGHTCUBESHADER).WhichType.at(COLOR), 1, &Color[0]);
	glUniformMatrix4fv(ShaderManager::GetShaderLocations(LIGHTCUBESHADER).WhichType.at(MODEL), 1, GL_FALSE, glm::value_ptr(model));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	return true;
}

bool Light::CreateCube()
{
	VertexPos Vertex[] = {
		{{-0.5f, -0.5f, -0.5f}},	//0
		{{ 0.5f, -0.5f, -0.5f}},	//1
		{{ 0.5f, -0.5f,  0.5f}},	//2
		{{-0.5f, -0.5f,  0.5f}},	//3

		{{-0.5f,  0.5f, -0.5f}},	//4
		{{ 0.5f,  0.5f, -0.5f}},	//5
		{{ 0.5f,  0.5f,  0.5f}},	//6
		{{-0.5f,  0.5f,  0.5f}},	//7
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
	lightPosition = glm::vec3(0.0f, 5.0f, 0.0f);
	glGenVertexArrays(1, &lightBuffer.VAO);
	glGenBuffers(1, &lightBuffer.EBO);
	glGenBuffers(1, &lightBuffer.VBO);
	glBindVertexArray(lightBuffer.VAO);

	glBindBuffer(GL_ARRAY_BUFFER, lightBuffer.VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex), Vertex, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lightBuffer.EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(normalArray), normalArray, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPos), 0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	return true;
}
		