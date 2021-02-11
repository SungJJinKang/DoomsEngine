#include "MeshRenderer.h"


doom::MeshRenderer::MeshRenderer() : Renderer(), mModelMatrixUniformLocation{ -1 }
{

}




void doom::MeshRenderer::SetMesh(graphics::Mesh* mesh)
{
	this->mTargetMesh = mesh;
}

void doom::MeshRenderer::SetMesh(graphics::Mesh& mesh)
{
	this->mTargetMesh = &mesh;
}

