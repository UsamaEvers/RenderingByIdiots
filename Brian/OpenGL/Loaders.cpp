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

	unsigned long len;
	std::ifstream file;
	file.open(filename, std::ios::in); // opens as ASCII!

	std::vector<glm::vec3> vertices;

	std::vector<glm::vec2> uvscpy;
	std::vector<glm::vec3> normalscpy;
	
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	std::vector<int> indices;

	std::string str;
	while (std::getline(file, str)) {

		std::vector<std::string> v;

		split(str, v, ' ');

		if (v[0] == "v")
		{
			glm::vec3 vertex(std::stof(v[1]), std::stof(v[2]), std::stof(v[3]));
			vertices.push_back(vertex);
		}
		else if (v[0] == "vt")
		{
			glm::vec2 uv(std::stof(v[1]), std::stof(v[2]));
			uvscpy.push_back(uv);
		}
		else if (v[0] == "vn")
		{
			glm::vec3 normal(std::stof(v[1]), std::stof(v[2]), std::stof(v[3]));
			normalscpy.push_back(normal);
		}
		if (v[0] == "f")
		{
			bool addNormal = false;
			for (int i = 1; i < 4; i++)
			{
				std::vector<std::string> val;

				split(v[i], val, '/');
				indices.push_back(std::stoi(val[0]) - 1);
			}
		}
	}
	uvs.resize(indices.size());
	normals.resize(indices.size());
	file.close();

	file.open(filename, std::ios::in); // opens as ASCII!

	while (std::getline(file, str)) 
	{

		std::vector<std::string> v;

		split(str, v, ' ');

		if (v[0] == "f")
		{
			bool addNormal = false;
			for (int i = 1; i < 4; i++)
			{
				std::vector<std::string> val;

				split(v[i], val, '/');
				int index = std::stoi(val[0]) - 1;
				if (val.size() > 1)
				{
					if (val[1] != "")
					{
						uvs[index] = uvscpy[std::stoi(val[1]) - 1];
					}
					else
					{
						uvs[index] = { 0., 0. };
					}
					if (val[2] != "")
					{
						normals[index] = normalscpy[std::stoi(val[2]) - 1];
					}
					else
					{
						normals[index] = { 0., 0., 0. };
					}
				}
				else
				{
					uvs.push_back({ 0., 0. });
					addNormal = true;
				}
			}
			if (addNormal)
			{
				glm::vec3 verts[3];
				for (int i = 1; i < 4; i++)
				{
					std::vector<std::string> val;

					split(v[i], val, '/');
					verts[i - 1] = vertices[std::stoi(val[0]) - 1];
				}
				glm::vec3 v1 = verts[1] - verts[0];
				glm::vec3 v2 = verts[2] - verts[0];
				glm::vec3 normal(glm::normalize(glm::cross(v1, v2)));
				for (int i = 1; i < 4; i++)
				{
					std::vector<std::string> val;

					split(v[i], val, '/');
					normals[std::stoi(val[0]) - 1] = normal;
				}
			}
		}
	}
	file.close();

	modelData.vertices = vertices;
	modelData.uvs = uvs;
	modelData.normals = normals;
	modelData.indices = indices;


	return modelData;
}
