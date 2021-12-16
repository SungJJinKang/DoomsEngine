#include "MeshRenderer.h"

#include "Asset/ThreeDModelAsset.h"


void dooms::MeshRenderer::OnDestroy()
{
	Base::OnDestroy();

}

void dooms::MeshRenderer::UpdateCullingEntityBlockViewer()
{
	Renderer::UpdateCullingEntityBlockViewer();

	if(IsValid(mTargetMesh) == true)
	{
		const ThreeDModelMesh* const threeDModelMesh = mTargetMesh->GetTargetThreeDModelMesh();

		
		mCullingEntityBlockViewer.SetMeshVertexData
		(
			reinterpret_cast<const culling::Vec3*>(threeDModelMesh->mMeshDatas.mVertex),
			threeDModelMesh->mMeshDatas.mVerticeCount,
			threeDModelMesh->mMeshIndices.data(),
			threeDModelMesh->mMeshIndices.size()
		);
	}
	
}

dooms::MeshRenderer::MeshRenderer() : Renderer(), mTargetMesh{ nullptr }
{

}

dooms::MeshRenderer::~MeshRenderer()
{
}

void dooms::MeshRenderer::SetMesh(const graphics::Mesh* const mesh)
{
	mTargetMesh = mesh;
	if (mTargetMesh != nullptr)
	{
		AddRendererToCullingSystem();

		const physics::Sphere& boudingSphere = mTargetMesh->GetBoundingSphere();
		/// <summary>
		/// MeshRenderer is required to UpdateLocalBVhColliderCache only when Mesh is changed
		/// </summary>
		/// <param name="mesh"></param>
		BVH_Sphere_Node_Object::UpdateLocalColliderCache(boudingSphere);
		ColliderUpdater<dooms::physics::AABB3D>::UpdateLocalColliderCache(mTargetMesh->GetBoundingBox());
		//BVH_Sphere_Node_Object::UpdateBVH_Node();

		//BVH_AABB3D_Node_Object::UpdateLocalBVhColliderCache(mTargetMesh->GetBoundingBox());
		//BVH_AABB3D_Node_Object::UpdateBVH_Node();
		//mIsBoundingSphereDirty.SetDirty(true);

		//SetBoundingSphereRadiusForCulling(boudingSphere.mRadius);
		//SetBoundingSphereRadiusForCulling(0);

		//TODO : when model matrix is changed, should update SetBoundingSphereRadiusForCulling

		UpdateCullingEntityBlockViewer();
	}
	else
	{
		RemoveRendererFromCullingSystem();
	}
}

dooms::physics::AABB3D dooms::MeshRenderer::GetLocalAABBBound() const
{
	if (mTargetMesh != nullptr)
	{
		return mTargetMesh->GetBoundingBox();
	}
	else
	{
		return {nullptr};
	}
}
