#include "Renderer.h"

#include "../Core/Graphics/Material/Material.h"
#include <Transform.h>
#include <Rendering/Camera.h>
#include "Graphics/Acceleration/LinearData_ViewFrustumCulling/EveryCulling.h"


void dooms::Renderer::SetRenderingFlag(const eRenderingFlag flag, const bool isSet)
{
	if (isSet == true)
	{
		mRenderingFlag |= static_cast<UINT32>(flag);
	}
	else
	{
		mRenderingFlag &= (~static_cast<UINT32>(flag));
	}
}

void dooms::Renderer::InitComponent()
{
	RendererComponentStaticIterator::GetSingleton()->AddRendererToStaticContainer(this);

	mEntityBlockViewer = graphics::Graphics_Server::GetSingleton()->mCullingSystem->AllocateNewEntity(this, GetTransform());

	AddLocalDirtyToTransformDirtyReceiver(BVH_Sphere_Node_Object::IsWorldColliderCacheDirty);
	AddLocalDirtyToTransformDirtyReceiver(ColliderUpdater<dooms::physics::AABB3D>::IsWorldColliderCacheDirty);
	AddLocalDirtyToTransformDirtyReceiver(bmIsModelMatrixDirty);

	//BVH_Sphere_Node_Object::UpdateWorldBVhColliderCache(true);
	
	//BVH_Sphere_Node_Object::InsertBVHLeafNode(graphics::Graphics_Server::GetSingleton()->mCullDistance., BVH_Sphere_Node_Object::GetWorldBVhColliderCacheByReference(), nullptr);
	//BVH_AABB3D_Node_Object::InsertBVHLeafNode(graphics::Graphics_Server::GetSingleton()->mViewFrustumCulling.mBVHSphere, BVH_AABB3D_Node_Object:::GetWorldBVhColliderCacheByReference(), nullptr);
}

const math::Matrix4x4& dooms::Renderer::GetModelMatrix()
{
	return GetTransform()->GetModelMatrix();
}

void dooms::Renderer::OnDestroy()
{
	graphics::Graphics_Server::GetSingleton()->mCullingSystem->RemoveEntityFromBlock(mEntityBlockViewer);

	RendererComponentStaticIterator::GetSingleton()->RemoveRendererToStaticContainer(this);
}

dooms::Renderer::Renderer() : ServerComponent(), mTargetMaterial{}
{

}

dooms::Renderer::~Renderer()
{
}


void dooms::Renderer::MergeBVHBitFlag()
{
	//mRenderingBitFlag |= graphics::eRenderingBitflag::IsVisible & ( BVH_Sphere_Node_Object::mBVH_Node_View->GetBitFlag() | BVH_AABB3D_Node_Object::mBVH_Node_View->GetBitFlag() );
}

void dooms::Renderer::ClearRenderingBitFlag()
{
	mRenderingFlag = 0;
}

void dooms::Renderer::SetMaterial(const graphics::Material* material) noexcept
{
	mTargetMaterial = material;
}

char dooms::Renderer::GetIsVisibleWithCameraIndex(UINT32 cameraIndex) const
{
	return mEntityBlockViewer.GetIsCulled(cameraIndex);
}

void dooms::Renderer::CacheDistanceToCamera(const size_t cameraIndex, const Camera* const camera)
{
	D_ASSERT(camera != nullptr);

	CacheDistanceToCamera(cameraIndex, camera->GetTransform()->GetPosition());
}

void dooms::Renderer::CacheDistanceToCamera(const size_t cameraIndex, const math::Vector3& cameraPos)
{
	if (mDistancesToCamera.size() <= cameraIndex)
	{
		mDistancesToCamera.resize(cameraIndex + 1);
	}

	mDistancesToCamera[cameraIndex] = (static_cast<const Transform*>(GetTransform())->GetPosition() - cameraPos).sqrMagnitude() - dooms::ColliderUpdater<dooms::physics::Sphere>::GetWorldCollider()->mRadius;
}

/*
const dooms::physics::Sphere& dooms::Renderer::GetBoudingSphere()
{
	UpdateWorldBVhColliderCache(false);
	if (mIsBoundingSphereDirty.GetIsDirty(true) == true)
	{
		mBoundingSphere = GetWorldBVhColliderCacheByReference();
	}
	return mBoundingSphere;
}
*/

void dooms::Renderer::SetMaterial(const graphics::Material& material) noexcept
{
	SetMaterial(&material);
}

