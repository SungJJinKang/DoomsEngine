#include "MeshRenderer.h"


doom::MeshRenderer::MeshRenderer() : Renderer(), mTargetMesh{ nullptr }
{

}

void doom::MeshRenderer::SetMesh(graphics::Mesh* mesh)
{
	this->mTargetMesh = mesh;
	if (this->mTargetMesh != nullptr)
	{
		this->UpdateLocalAABB3D(this->mTargetMesh->GetAABB());
	}
	else
	{
		this->UpdateLocalAABB3D({});
	}
}