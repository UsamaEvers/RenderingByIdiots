#pragma once

#include "Component.h"

class Mesh;
class Camera;

class MeshRenderer : public Component
{
public:
	static std::string GetName() { return "MeshRenderer"; }

	MeshRenderer();
	MeshRenderer(Mesh* mesh);
	~MeshRenderer();

	void Render(Camera cam);

private:
	Mesh* m_Mesh;
};