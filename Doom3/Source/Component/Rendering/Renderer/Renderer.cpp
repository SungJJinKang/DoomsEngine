#include "Renderer.h"

#include "../Core/Graphics/Material/Material.h"
#include <Transform.h>
#include <Rendering/Camera.h>
#include <Graphics/Acceleration/LinearData_ViewFrustumCulling/EveryCulling.h>
#include <Graphics/Graphics_Server.h>

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

	AddRendererToCullingSystem();

	AddLocalDirtyToTransformDirtyReceiver(BVH_AABB3D_Node_Object::IsWorldColliderCacheDirty);
	//AddLocalDirtyToTransformDirtyReceiver(ColliderUpdater<dooms::physics::AABB3D>::IsWorldColliderCacheDirty);
	AddLocalDirtyToTransformDirtyReceiver(bmIsModelMatrixDirty);

	InsertBVHLeafNode(graphics::Graphics_Server::GetSingleton()->mRendererColliderBVH, *BVH_AABB3D_Node_Object::GetWorldCollider(), nullptr);

	//BVH_Sphere_Node_Object::UpdateWorldBVhColliderCache(true);
	
	//BVH_Sphere_Node_Object::InsertBVHLeafNode(graphics::Graphics_Server::GetSingleton()->mCullDistance., BVH_Sphere_Node_Object::GetWorldBVhColliderCacheByReference(), nullptr);
	//BVH_AABB3D_Node_Object::InsertBVHLeafNode(graphics::Graphics_Server::GetSingleton()->mViewFrustumCulling.mBVHSphere, BVH_AABB3D_Node_Object:::GetWorldBVhColliderCacheByReference(), nullptr);
	
}

void dooms::Renderer::UpdateComponent()
{
				
}

const math::Matrix4x4& dooms::Renderer::GetModelMatrix()
{
	return GetTransform()->GetModelMatrix();
}

void dooms::Renderer::OnActivated()
{
	Component::OnActivated();

	mCullingEntityBlockViewer.SetIsObjectEnabled(true);
}

void dooms::Renderer::OnDeActivated()
{
	Component::OnDeActivated();

	if(mCullingEntityBlockViewer.GetIsActive() == true)
	{
		mCullingEntityBlockViewer.SetIsObjectEnabled(false);
	}
	
}

void dooms::Renderer::AddRendererToCullingSystem()
{
	if(mCullingEntityBlockViewer.GetIsActive() == false)
	{
		mCullingEntityBlockViewer = graphics::Graphics_Server::GetSingleton()->mCullingSystem->AllocateNewEntity();
		InitializeCullingEntityBlockViewer();
	}
}

void dooms::Renderer::RemoveRendererFromCullingSystem()
{
	graphics::Graphics_Server::GetSingleton()->mCullingSystem->RemoveEntityFromBlock(mCullingEntityBlockViewer);
}

void dooms::Renderer::OnDestroy()
{
	Base::OnDestroy();

	RemoveBVH_Node();

	RemoveRendererFromCullingSystem();

	RendererComponentStaticIterator::GetSingleton()->RemoveRendererToStaticContainer(this);
}

dooms::Renderer::Renderer() : Component(), mTargetMaterial{nullptr}, mCullingEntityBlockViewer()
{

}

dooms::Renderer::~Renderer()
{
}

void dooms::Renderer::PreRender()
{
	if(GetIsComponentEnabled() == true)
	{
		mCullingEntityBlockViewer.SetObjectWorldPosition(GetTransform()->GetPosition().data());

		const physics::AABB3D* const aabb = ColliderUpdater<physics::AABB3D>::GetWorldCollider();
		mCullingEntityBlockViewer.SetAABBWorldPosition(aabb->mLowerBound.data(), aabb->mUpperBound.data());

		mCullingEntityBlockViewer.SetModelMatrix(GetTransform()->GetModelMatrix().data());
	}

	

}


void dooms::Renderer::MergeBVHBitFlag()
{
	//mRenderingBitFlag |= graphics::eRenderingBitflag::IsVisible & ( BVH_Sphere_Node_Object::mBVH_Node_View->GetBitFlag() | BVH_AABB3D_Node_Object::mBVH_Node_View->GetBitFlag() );
}

void dooms::Renderer::ClearRenderingBitFlag()
{
	mRenderingFlag = 0;
}

void dooms::Renderer::InitializeCullingEntityBlockViewer()
{

}

void dooms::Renderer::UpdateCullingEntityBlockViewer()
{
	
}

void dooms::Renderer::SetMaterial(const graphics::Material* material) noexcept
{
	mTargetMaterial = material;
}

char dooms::Renderer::GetIsVisibleWithCameraIndex(UINT32 cameraIndex) const
{
	return mCullingEntityBlockViewer.GetIsCulled(cameraIndex);
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

	mDistancesToCamera[cameraIndex] = (static_cast<const Transform*>(GetTransform())->GetPosition() - cameraPos).magnitude() - dooms::ColliderUpdater<dooms::physics::AABB3D>::GetWorldCollider()->GetDiagonarLineLength();
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

