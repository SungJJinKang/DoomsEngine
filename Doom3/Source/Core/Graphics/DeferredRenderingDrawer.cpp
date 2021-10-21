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

	doom::graphics::GraphicsAPI::DepthMask(false);
	mQuadMesh->Draw();
	doom::graphics::GraphicsAPI::DepthMask(true);
}

void doom::graphics::DeferredRenderingDrawer::SetShaderToGBufferMaterial()
{
	doom::asset::ShaderAsset* const gBufferDrawerShader = doom::assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::SHADER>("GbufferDrawer.glsl");
	mGbufferDrawerMaterial.SetShaderAsset(gBufferDrawerShader);
}
