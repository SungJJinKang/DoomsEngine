#include "Renderer.h"
#include "../Core/Graphics/Material.h"
#include <Transform.h>


void doom::Renderer::SetLocalAABB3D(const physics::AABB3D& aabb3d)
{
	this->mLocalAABB3D.mLowerBound = aabb3d.mLowerBound;
	this->mLocalAABB3D.mUpperBound = aabb3d.mUpperBound;
	this->IsWorldAABBDirty = true;
}

doom::physics::AABB3D doom::Renderer::GetWorldAABB3D()
{
	if (this->IsWorldAABBDirty.GetIsDirty(true))
	{
		this->UpdateWorldAABB3D();
	}
	return this->mWorldAABB3D;
}

const doom::physics::AABB3D& doom::Renderer::GetLocalAABB3D() const
{
	return this->mLocalAABB3D;
}

doom::physics::AABB3D doom::Renderer::GetLocalAABB3D()
{
	return this->mLocalAABB3D;
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

void doom::Renderer::SetMaterial(graphics::Material& material) noexcept
{
	this->SetMaterial(&material);
}

void doom::Renderer::UpdateWorldAABB3D()
{
	this->mWorldAABB3D.mLowerBound = this->GetTransform()->GetModelMatrix() * this->mLocalAABB3D.mLowerBound;
	this->mWorldAABB3D.mUpperBound = this->GetTransform()->GetModelMatrix() * this->mLocalAABB3D.mUpperBound;
}
