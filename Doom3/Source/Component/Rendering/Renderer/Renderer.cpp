#include "Renderer.h"
#include "../Core/Graphics/Material.h"
#include <Transform.h>




doom::Renderer::Renderer() : ServerComponent(), StaticContainer(), mTargetMaterial{}
{

}

void doom::Renderer::DrawAABB3D()
{
	this->GetWorldAABB3DByReference().DrawPhysicsDebugColor(graphics::eColor::Green);
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

