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

glm::vec3 GetPosition(std::string str)
{
	int i = 0;
	while (str[i] != ' ')
	{
		i++;
	}

	glm::vec3 pos;

	for (int f = 0; f < 3; f++)
	{
		i++;
		std::string value;
		while (str[i] != ' ')
		{
			value.push_back(str[i]);
			i++;
			if (i == str.length())
			{
				break;
			}
		}
		pos[f] = std::stof(value);
	}
	return pos;
}

glm::vec2 GetUv(std::string str)
{
	int i = 0;
	while (str[i] != ' ')
	{ 
		i++;
	}

	glm::vec2 uv;
	
	for (int f = 0; f < 2; f++)
	{
		i++;
		std::string value;
		while (str[i] != ' ')
		{
			value.push_back(str[i]);
			i++;
			if (i == str.length())
			{
				break;
			}
		}
		uv[f] = std::stof(value);
	}
	return uv;
}

void AddIndices(std::vector<int>& indices, std::string str)
{
	int f = 0;
	while (str[f] != ' ')
	{
		f++;
	}
	f++;
	for (int i = 0; i < 3; i++)
	{
		std::string val;
		while (str[f] != '/')
		{
			val.push_back(str[f]);
			f++;
			if (f == str.length())
			{
				break;
			}
		}
		indices.push_back(std::stoi(val)-1);
		if (f == str.length())
		{
			break;
		}
		while (str[f] != ' ')
		{
			f++;
			if (f == str.length())
			{
				break;
			}
		}
		f++;
	}
}

ModelData Loaders::LoadModel(std::string filename)
{
	ModelData modelData;

	unsigned long len;
	std::ifstream file;
	file.open(filename, std::ios::in); // opens as ASCII!

	std::vector<Vertex> vertices;
	std::vector<int> indices;

	int textureIndex = 0;

	std::string str;
	while (std::getline(file, str)) {
		switch (str[0])
		{
		case 'v':
			switch (str[1])
			{
			case ' ':
				vertices.push_back({ GetPosition(str), {0., 0.} });
				break;
			case 't':
				if (textureIndex < vertices.size())
					vertices[textureIndex].uv = GetUv(str);
				textureIndex++;
				break;
			case 'n':
				break;
			}
			break;
		case 'f':
			AddIndices(indices, str);
			break;
		}
	}
	
	modelData.vertices = vertices;
	modelData.indices = indices;

	file.close();

	return modelData;
}
