#include "Renderer.h"

#include "../Core/Graphics/Material/Material.h"
#include <Transform.h>
#include <Rendering/Camera.h>
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

void doom::Renderer::CacheDistanceToCamera(const size_t cameraIndex, const Camera* const camera)
{
	D_ASSERT(camera != nullptr);

	if (mDistancesToCamera.size() <= cameraIndex)
	{
		mDistancesToCamera.resize(cameraIndex + 1);
	}

	mDistancesToCamera[cameraIndex] = (static_cast<const Transform*>(GetTransform())->GetPosition() - camera->GetTransform()->GetPosition()).sqrMagnitude() - BVH_Sphere_Node_Object::GetWorldCollider()->mRadius;
	
	

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

