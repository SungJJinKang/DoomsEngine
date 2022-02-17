#include "Renderer.h"

#include <Rendering/Material/Material.h>
#include <Transform.h>
#include <Rendering/Camera.h>
#include <Rendering/Pipeline/PipeLines/DefaultGraphcisPipeLine.h>
#include <Rendering/Graphics_Server.h>
#include <Rendering/Batch/BatchRenderingManager.h>

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
	
	AddLocalDirtyToTransformDirtyReceiver(BVH_AABB3D_Node_Object::IsWorldColliderCacheDirty);
	//AddLocalDirtyToTransformDirtyReceiver(ColliderUpdater<dooms::physics::AABB3D>::IsWorldColliderCacheDirty);
	AddLocalDirtyToTransformDirtyReceiver(bmIsModelMatrixDirty);

	InsertBVHLeafNode(graphics::Graphics_Server::GetSingleton()->mRendererColliderBVH, *BVH_AABB3D_Node_Object::GetWorldCollider(), nullptr);
	UpdateRendererBatchRendering();
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

}

void dooms::Renderer::OnDeActivated()
{
	Component::OnDeActivated();

	if(mCullingEntityBlockViewer.IsValid() == true)
	{
		mCullingEntityBlockViewer.SetIsObjectEnabled(false);
	}
	
}

void dooms::Renderer::AddRendererToCullingSystem()
{
	if(mCullingEntityBlockViewer.IsValid() == false)
	{
		graphics::DefaultGraphcisPipeLine* defaultGraphicsPipeLine = CastTo<graphics::DefaultGraphcisPipeLine*>(dooms::graphics::GraphicsPipeLine::GetSingleton());
		D_ASSERT(IsValid(defaultGraphicsPipeLine));
		if (IsValid(defaultGraphicsPipeLine))
		{
			mCullingEntityBlockViewer = defaultGraphicsPipeLine->mRenderingCullingManager.mCullingSystem->AllocateNewEntity();
		}
		InitializeCullingEntityBlockViewer();
	}
}

void dooms::Renderer::RemoveRendererFromCullingSystem()
{
	if (mCullingEntityBlockViewer.IsValid() == true)
	{
		graphics::DefaultGraphcisPipeLine* defaultGraphicsPipeLine = CastTo<graphics::DefaultGraphcisPipeLine*>(dooms::graphics::GraphicsPipeLine::GetSingleton());
		D_ASSERT(IsValid(defaultGraphicsPipeLine));
		if (IsValid(defaultGraphicsPipeLine))
		{
			defaultGraphicsPipeLine->mRenderingCullingManager.mCullingSystem->RemoveEntityFromBlock(mCullingEntityBlockViewer);
		}
	}
}

void dooms::Renderer::OnChangedByGUI(const dooms::reflection::DField& field_of_changed_field)
{
	Component::OnChangedByGUI(field_of_changed_field);

	if(field_of_changed_field.CompareWithFieldName("mDesiredMaxDrawDistance") == true)
	{
		SetDesiredMaxDrawDistance(mDesiredMaxDrawDistance);
	}
}

void dooms::Renderer::UpdateRendererBatchRendering()
{
	const eEntityMobility entityMobility = GetOwnerEntity()->GetEntityMobility();
	switch (entityMobility)
	{
		case Static:
			if (IsBatchable())
			{
				const bool isSuccess = graphics::BatchRenderingManager::GetSingleton()->AddRendererToBatchRendering(this, GetCapableBatchRenderingType());;
				if (isSuccess)
				{
					bmIsBatched = true;
					RemoveRendererFromCullingSystem();
				}
			}
		break;
		case Dynamic:
			{
				const bool isSuccess = graphics::BatchRenderingManager::GetSingleton()->RemoveRendererFromBatchRendering(this);
				if (isSuccess)
				{
					bmIsBatched = false;
					AddRendererToCullingSystem();
				}
			}
		break;
	}
}

void dooms::Renderer::OnDestroy()
{
	Base::OnDestroy();

	RemoveBVH_Node();

	RemoveRendererFromCullingSystem();

	if(IsValid(RendererComponentStaticIterator::GetSingleton()))
	{
		RendererComponentStaticIterator::GetSingleton()->RemoveRendererToStaticContainer(this);
	}

	graphics::BatchRenderingManager::GetSingleton()->RemoveRendererFromBatchRendering(this);

}

dooms::Renderer::Renderer() : Component(), mTargetMaterial{nullptr}, mCullingEntityBlockViewer(), bmIsBatched(false)
{

}

dooms::Renderer::~Renderer()
{
}

void dooms::Renderer::PreRender()
{
	if(GetIsComponentEnabled() == true)
	{
		const physics::AABB3D* const aabb = ColliderUpdater<physics::AABB3D>::GetWorldCollider();

		mCullingEntityBlockViewer.UpdateEntityData
		(
			GetTransform()->GetPosition().data(),
			aabb->mLowerBound.data(),
			aabb->mUpperBound.data(),
			GetTransform()->GetModelMatrix().data()
		);
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
	mCullingEntityBlockViewer.SetDesiredMaxDrawDistance(mDesiredMaxDrawDistance);
	mCullingEntityBlockViewer.SetIsObjectEnabled(true);
}

void dooms::Renderer::UpdateCullingEntityBlockViewer()
{
	
}

void dooms::Renderer::SetMaterial(graphics::Material* material) noexcept
{
	mTargetMaterial = material;
}

void dooms::Renderer::SetMaterial(graphics::Material& material) noexcept
{
	SetMaterial(&material);
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


void dooms::Renderer::SetDesiredMaxDrawDistance(const FLOAT32 desiredMaxDrawDistance)
{
	mDesiredMaxDrawDistance = desiredMaxDrawDistance;
	mCullingEntityBlockViewer.SetDesiredMaxDrawDistance(mDesiredMaxDrawDistance);
}

FLOAT32 dooms::Renderer::GetDesiredMaxDrawDistance() const
{
	return mDesiredMaxDrawDistance;
}

void dooms::Renderer::OnEntityMobilityChanged(const eEntityMobility entityMobility)
{
	Component::OnEntityMobilityChanged(entityMobility);

	UpdateRendererBatchRendering();
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



