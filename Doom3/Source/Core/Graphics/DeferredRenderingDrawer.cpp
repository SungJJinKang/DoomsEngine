#include "DeferredRenderingDrawer.h"

#include <Game/AssetManager/AssetManager.h>


void dooms::graphics::DeferredRenderingDrawer::Initialize()
{
	SetShaderToGBufferMaterial();
	mQuadMesh = Mesh::GetQuadMesh();
}

dooms::graphics::DeferredRenderingDrawer::DeferredRenderingDrawer()
	:mQuadMesh()
{
}

dooms::graphics::DeferredRenderingDrawer::~DeferredRenderingDrawer()
{

}

void dooms::graphics::DeferredRenderingDrawer::DrawDeferredRenderingQuadDrawer()
{
	mGbufferDrawerMaterial.UseProgram();

	dooms::graphics::GraphicsAPI::DepthMask(false);
	mQuadMesh->Draw();
	dooms::graphics::GraphicsAPI::DepthMask(true);
}

void dooms::graphics::DeferredRenderingDrawer::SetShaderToGBufferMaterial()
{
	dooms::asset::ShaderAsset* const gBufferDrawerShader = dooms::assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::SHADER>("GbufferDrawer.glsl");
	mGbufferDrawerMaterial.SetShaderAsset(gBufferDrawerShader);
}
