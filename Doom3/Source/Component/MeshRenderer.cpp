#include "MeshRenderer.h"


doom::MeshRenderer::MeshRenderer() : Renderer(), mTargetMesh{ nullptr }
{

}

void doom::MeshRenderer::SetMesh(graphics::Mesh* mesh)
{
	this->mTargetMesh = mesh;
	if (this->mTargetMesh != nullptr)
	{
		this->SetLocalAABB3D(this->mTargetMesh->GetAABB());
	}
	else
	{
		this->SetLocalAABB3D({});
	}
}