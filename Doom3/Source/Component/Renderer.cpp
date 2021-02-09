#include "Renderer.h"


doom::Renderer::Renderer() : mTargetMaterial{}
{

}


doom::Renderer::~Renderer()
{

}

void doom::Renderer::SetMaterial(graphics::Material* material)
{
	this->mTargetMaterial = material;
}

