#include "Renderer.h"

doom::Renderer::Renderer() : CoreComponent(), ComponentStaticIterater(), mTargetMaterial{}
{

}


doom::Renderer::~Renderer()
{

}

void doom::Renderer::SetMaterial(graphics::Material* material)
{
	this->mTargetMaterial = material;
}

void doom::Renderer::SetMaterial(graphics::Material& material)
{
	this->SetMaterial(&material);
}

