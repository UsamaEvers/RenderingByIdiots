#include "Loaders.h"
#include "Mesh.h"

#include <fstream>

unsigned long getFileLength(std::ifstream& file)
{
	if (!file.good()) return 0;

	unsigned long pos = file.tellg();
	file.seekg(0, std::ios::end);
	unsigned long len = file.tellg();
	file.seekg(std::ios::beg);

	return len;
}

size_t split(const std::string& txt, std::vector<std::string>& strs, char ch)
{
	size_t pos = txt.find(ch);
	size_t initialPos = 0;
	strs.clear();

	// Decompose statement
	while (pos != std::string::npos) {
		strs.push_back(txt.substr(initialPos, pos - initialPos));
		initialPos = pos + 1;

		pos = txt.find(ch, initialPos);
	}

	// Add the last one
	strs.push_back(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));

	return strs.size();
}

char* Loaders::Loadshader(std::string filename)
{
	unsigned long len;
	std::ifstream file;
	file.open(filename, std::ios::in); // opens as ASCII!

	len = getFileLength(file);

	char* ShaderSource;

	ShaderSource = (char*) new char[len + 1];

	// len isn't always strlen cause some characters are stripped in ascii read...
	// it is important to 0-terminate the real length later, len is just max possible value... 
	ShaderSource[len] = 0;

	unsigned int i = 0;
	while (file.good())
	{
		ShaderSource[i] = file.get();       // get character from file.
		if (!file.eof())
			i++;
	}

	ShaderSource[i] = 0;  // 0-terminate it at the correct position

	file.close();

	return ShaderSource;
}

ModelData Loaders::LoadModel(std::string filename)
{
	ModelData modelData;

	FILE* file = fopen(filename.c_str(), "r");
	if (file == NULL) {
		printf("Impossible to open the file !\n");
	}

	std::vector<glm::vec3> vertices;

	std::vector<glm::vec2> uvscpy;
	std::vector<glm::vec3> normalscpy;
	
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	std::vector<int> indices;

	while (1) {

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader
		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			uvscpy.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			normalscpy.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			uvs.resize(vertices.size());
			normals.resize(vertices.size());
			break;
		}
	}
	while (1) {

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
			}
			indices.push_back(vertexIndex[0]-1);
			indices.push_back(vertexIndex[1]-1);
			indices.push_back(vertexIndex[2]-1);
			uvs[vertexIndex[0]-1] = uvscpy[uvIndex[0]-1];
			uvs[vertexIndex[1]-1] = uvscpy[uvIndex[1]-1];
			uvs[vertexIndex[2]-1] = uvscpy[uvIndex[2]-1];
			normals[vertexIndex[0]-1] = normalscpy[normalIndex[0]-1];
			normals[vertexIndex[1]-1] = normalscpy[normalIndex[1]-1];
			normals[vertexIndex[2]-1] = normalscpy[normalIndex[2]-1];
		}
	}

	modelData.vertices = vertices;
	modelData.uvs = uvs;
	modelData.normals = normals;
	modelData.indices = indices;


	return modelData;
}
