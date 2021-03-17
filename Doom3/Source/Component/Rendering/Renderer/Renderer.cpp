#include "Renderer.h"
#include "../Core/Graphics/Material.h"
#include <Transform.h>

void doom::Renderer::InitComponent()
{
	RendererComponentStaticIterator::AddRendererToStaticContainer();

	this->AddLocalDirtyToTransformDirtyReceiver(this->IsWorldBVhAABBCacheDirty);
	this->AddLocalDirtyToTransformDirtyReceiver(this->mIsBoundingSphereDirty);
	//this->InsertBVHLeafNode(graphics::Graphics_Server::GetSingleton()->mViewFrustumCulling.mViewFrustumBVH, this->GetWorldBVhAABB3DCacheByReference(), nullptr);
}

const math::Matrix4x4& doom::Renderer::GetModelMatrix() const
{
	return this->GetTransform()->GetModelMatrix();
}

doom::Renderer::Renderer() : ServerComponent(), StaticContainer(), mTargetMaterial{}
{

}

void doom::Renderer::BindMaterial() noexcept
{
	if (this->mTargetMaterial != nullptr)
	{
		this->mTargetMaterial->UseProgram();
	}
}

void doom::Renderer::SetMaterial(graphics::Material* material) noexcept
{
	this->mTargetMaterial = material;
}

const doom::physics::Sphere& doom::Renderer::GetBoudingSphere()
{
	this->UpdateWorldBVhAABBCache(false);
	if (mIsBoundingSphereDirty.GetIsDirty(true) == true)
	{
		this->mBoundingSphere = this->GetWorldBVhAABB3DCacheByReference();
	}
	return this->mBoundingSphere;
}

void doom::Renderer::SetMaterial(graphics::Material& material) noexcept
{
	this->SetMaterial(&material);
}

