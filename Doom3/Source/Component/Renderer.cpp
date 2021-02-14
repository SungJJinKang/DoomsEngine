#include "Renderer.h"
#include "../Core/Graphics/Material.h"
doom::Renderer::Renderer() : ServerComponent(), ComponentStaticIterater(), mTargetMaterial{}
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

