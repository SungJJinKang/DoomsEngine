#include "DeferredRenderingDrawer.h"

#include <Game/AssetManager/AssetManager.h>


void doom::graphics::DeferredRenderingDrawer::Initialize()
{
	SetShaderToGBufferMaterial();
	mQuadMesh = Mesh::GetQuadMesh();
}

doom::graphics::DeferredRenderingDrawer::DeferredRenderingDrawer()
	:mQuadMesh()
{
}

doom::graphics::DeferredRenderingDrawer::~DeferredRenderingDrawer()
{

}

void doom::graphics::DeferredRenderingDrawer::DrawDeferredRenderingQuadDrawer()
{
	mGbufferDrawerMaterial.UseProgram();

	mQuadMesh->Draw();
}

void doom::graphics::DeferredRenderingDrawer::SetShaderToGBufferMaterial()
{
	doom::asset::ShaderAsset* const gBufferDrawerShader = doom::assetimporter::AssetManager::GetAsset<asset::eAssetType::SHADER>("GbufferDrawer.glsl");
	mGbufferDrawerMaterial.SetShaderAsset(gBufferDrawerShader);
}
