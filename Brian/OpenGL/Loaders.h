#pragma once
#include <string>
#include <vector>

struct ModelData;

class Loaders
{
public:
	static char* Loadshader(std::string filename);

	static ModelData LoadModel(std::string filename);
};

