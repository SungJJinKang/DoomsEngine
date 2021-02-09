#include "MeshRenderer.h"


doom::MeshRenderer::MeshRenderer() : Renderer()
{

}




doom::MeshRenderer::MeshRenderer(graphics::Mesh* targetMesh, graphics::Material* targetMaterial) : Renderer(targetMaterial), mTargetMesh{ targetMesh }
{

}

