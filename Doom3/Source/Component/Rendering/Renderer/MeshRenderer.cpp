#include "MeshRenderer.h"


doom::MeshRenderer::MeshRenderer() : Renderer(), mTargetMesh{ nullptr }
{

}

void doom::MeshRenderer::SetMesh(graphics::Mesh* mesh)
{
	this->mTargetMesh = mesh;
	if (this->mTargetMesh != nullptr)
	{
		/// <summary>
		/// MeshRenderer is required to UpdateLocalBVhAABBCache only when Mesh is changed
		/// </summary>
		/// <param name="mesh"></param>
		this->UpdateLocalBVhAABBCache(this->mTargetMesh->GetAABB());
		mIsBoundingSphereDirty.SetDirty(true);
	}
	else
	{
		D_DEBUG_LOG("MeshRender don't have for BVH_AABB", eLogType::D_ERROR);
	}
}