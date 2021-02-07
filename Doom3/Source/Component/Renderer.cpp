#include "Renderer.h"


doom::Renderer::Renderer() : mTargetMaterial{}
{

}


doom::Renderer::~Renderer()
{

}

doom::Renderer::Renderer(graphics::Material* targetMaterial) : mTargetMaterial{ targetMaterial }
{

}
