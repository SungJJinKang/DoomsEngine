#include "MeshRenderer.h"


doom::MeshRenderer::MeshRenderer() : Renderer(), mTargetMesh{ nullptr }
{

}

void doom::MeshRenderer::SetMesh(const graphics::Mesh* const mesh)
{
	mTargetMesh = mesh;
	if (mTargetMesh != nullptr)
	{
		auto boudingSphere = mTargetMesh->GetBoundingSphere();
		/// <summary>
		/// MeshRenderer is required to UpdateLocalBVhColliderCache only when Mesh is changed
		/// </summary>
		/// <param name="mesh"></param>
		BVH_Sphere_Node_Object::UpdateLocalColliderCache(boudingSphere);
		ColliderUpdater<doom::physics::AABB3D>::UpdateLocalColliderCache(mTargetMesh->GetBoundingBox());
		//BVH_Sphere_Node_Object::UpdateBVH_Node();

		//BVH_AABB3D_Node_Object::UpdateLocalBVhColliderCache(mTargetMesh->GetBoundingBox());
		//BVH_AABB3D_Node_Object::UpdateBVH_Node();
		//mIsBoundingSphereDirty.SetDirty(true);

		//SetBoundingSphereRadiusForCulling(boudingSphere.mRadius);
		//SetBoundingSphereRadiusForCulling(0);

		//TODO : when model matrix is changed, should update SetBoundingSphereRadiusForCulling
	}
	else
	{
		D_DEBUG_LOG("MeshRender don't have for BVH_AABB", eLogType::D_ERROR);
	}
}

doom::physics::AABB3D doom::MeshRenderer::GetLocalAABBBound() const
{
	if (mTargetMesh != nullptr)
	{
		return mTargetMesh->GetBoundingBox();
	}
	else
	{
		return {};
	}
}
