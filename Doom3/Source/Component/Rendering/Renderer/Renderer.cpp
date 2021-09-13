#include "Renderer.h"

#include "../Core/Graphics/Material.h"
#include <Transform.h>
#include "Graphics/Acceleration/LinearData_ViewFrustumCulling/EveryCulling.h"


void doom::Renderer::InitComponent()
{
	RendererComponentStaticIterator::AddRendererToStaticContainer();

	mEntityBlockViewer = graphics::Graphics_Server::GetSingleton()->mCullingSystem->AllocateNewEntity(this);

	AddLocalDirtyToTransformDirtyReceiver(BVH_Sphere_Node_Object::IsWorldColliderCacheDirty);
	AddLocalDirtyToTransformDirtyReceiver(ColliderUpdater<doom::physics::AABB3D>::IsWorldColliderCacheDirty);

	//BVH_Sphere_Node_Object::UpdateWorldBVhColliderCache(true);
	
	//BVH_Sphere_Node_Object::InsertBVHLeafNode(graphics::Graphics_Server::GetSingleton()->mCullDistance., BVH_Sphere_Node_Object::GetWorldBVhColliderCacheByReference(), nullptr);
	//BVH_AABB3D_Node_Object::InsertBVHLeafNode(graphics::Graphics_Server::GetSingleton()->mViewFrustumCulling.mBVHSphere, BVH_AABB3D_Node_Object:::GetWorldBVhColliderCacheByReference(), nullptr);
}

const math::Matrix4x4& doom::Renderer::GetModelMatrix()
{
	return GetTransform()->GetModelMatrix();
}

void doom::Renderer::OnDestroy()
{
	graphics::Graphics_Server::GetSingleton()->mCullingSystem->RemoveEntityFromBlock(mEntityBlockViewer);
}

doom::Renderer::Renderer() : ServerComponent(), StaticContainer(), mTargetMaterial{}
{

}


void doom::Renderer::MergeBVHBitFlag()
{
	//mRenderingBitFlag |= graphics::eRenderingBitflag::IsVisible & ( BVH_Sphere_Node_Object::mBVH_Node_View->GetBitFlag() | BVH_AABB3D_Node_Object::mBVH_Node_View->GetBitFlag() );
}

void doom::Renderer::ClearRenderingBitFlag()
{
	mRenderingBitFlag = 0;
}

void doom::Renderer::SetMaterial(graphics::Material* material) noexcept
{
	mTargetMaterial = material;
}

char doom::Renderer::GetIsVisibleWithCameraIndex(unsigned int cameraIndex)
{
	return mEntityBlockViewer.GetIsCulled(cameraIndex);
}

bool doom::Renderer::GetIsCulled(unsigned int cameraIndexled) const
{
	return mEntityBlockViewer.GetIsCulled(cameraIndexled);
}

/*
const doom::physics::Sphere& doom::Renderer::GetBoudingSphere()
{
	UpdateWorldBVhColliderCache(false);
	if (mIsBoundingSphereDirty.GetIsDirty(true) == true)
	{
		mBoundingSphere = GetWorldBVhColliderCacheByReference();
	}
	return mBoundingSphere;
}
*/

void doom::Renderer::SetMaterial(graphics::Material& material) noexcept
{
	SetMaterial(&material);
}

