#include "Renderer.h"
#include "../Core/Graphics/Material.h"
#include <Transform.h>




const math::Matrix4x4& doom::Renderer::GetModelMatrix() const
{
	return this->GetTransform()->GetModelMatrix();
}

doom::Renderer::Renderer() : ServerComponent(), StaticContainer(), mTargetMaterial{}
{

}

void doom::Renderer::DrawAABB3D()
{
	this->GetWorld_BVH_AABB3D().DrawPhysicsDebugColor(graphics::eColor::Green);
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

