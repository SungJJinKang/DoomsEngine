#include "MeshRenderer.h"


doom::MeshRenderer::MeshRenderer() : Renderer(), mTargetMesh{ nullptr }
{

}

void doom::MeshRenderer::SetMesh(graphics::Mesh* mesh)
{
	this->mTargetMesh = mesh;
	if (this->mTargetMesh != nullptr)
	{
		auto boudingSphere = this->mTargetMesh->GetSphere();
		/// <summary>
		/// MeshRenderer is required to UpdateLocalBVhColliderCache only when Mesh is changed
		/// </summary>
		/// <param name="mesh"></param>
		BVH_Sphere_Node_Object::UpdateLocalColliderCache(boudingSphere);
		ColliderUpdater<doom::physics::AABB3D>::UpdateLocalColliderCache(this->mTargetMesh->GetAABB());
		//BVH_Sphere_Node_Object::UpdateBVH_Node();

		//BVH_AABB3D_Node_Object::UpdateLocalBVhColliderCache(this->mTargetMesh->GetAABB());
		//BVH_AABB3D_Node_Object::UpdateBVH_Node();
		//mIsBoundingSphereDirty.SetDirty(true);

		this->SetBoundingSphereRadiusForCulling(boudingSphere.mRadius);
		//this->SetBoundingSphereRadiusForCulling(0);

		//TODO : when model matrix is changed, should update SetBoundingSphereRadiusForCulling
	}
	else
	{
		D_DEBUG_LOG("MeshRender don't have for BVH_AABB", eLogType::D_ERROR);
	}
}

doom::physics::AABB3D doom::MeshRenderer::GetLocalAABBBound() const
{
	if (this->mTargetMesh != nullptr)
	{
		return this->mTargetMesh->GetAABB();
	}
	else
	{
		return {};
	}
}
