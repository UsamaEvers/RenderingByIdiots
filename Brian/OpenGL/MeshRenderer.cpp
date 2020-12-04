#include "MeshRenderer.h"

#include "Entity.h"
#include "Mesh.h"
#include "Camera.h"
#include "Transform.h"

MeshRenderer::MeshRenderer() 
	: Component(GetName())
{
}

MeshRenderer::MeshRenderer(Mesh* mesh)
	: Component(GetName())
{
	m_Mesh = mesh;
}

MeshRenderer::~MeshRenderer() 
{
	m_Mesh = nullptr;
}

void MeshRenderer::Render(Camera cam)
{
	m_Mesh->Render(GetParent()->GetComponent<Transform>(), cam);
}