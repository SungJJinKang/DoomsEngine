#include "MeshRenderer.h"


doom::MeshRenderer::MeshRenderer() : Renderer()
{

}


void doom::MeshRenderer::UpdateComponent()
{
	this->Draw();
}

doom::MeshRenderer::MeshRenderer(graphics::Mesh* targetMesh, graphics::Material* targetMaterial) : Renderer(targetMaterial), mTargetMesh{ targetMesh }
{

}

