#include "MeshRenderer.h"


doom::MeshRenderer::MeshRenderer() : Renderer()
{

}




void doom::MeshRenderer::SetMesh(graphics::Mesh* mesh)
{
	this->mTargetMesh = mesh;
}



