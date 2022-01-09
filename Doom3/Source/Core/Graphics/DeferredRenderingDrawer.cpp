#include "DeferredRenderingDrawer.h"

#include <Game/AssetManager/AssetManager.h>
#include "Buffer/MeshHelper.h"

void dooms::graphics::DeferredRenderingDrawer::Initialize()
{
	SetShaderToGBufferMaterial();
	mQuadMesh = meshHelper::GetQuadMesh();
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

	dooms::graphics::GraphicsAPI::SetDepthMask(false);
	mQuadMesh->Draw();
	dooms::graphics::GraphicsAPI::SetDepthMask(true);
}

void dooms::graphics::DeferredRenderingDrawer::SetShaderToGBufferMaterial()
{
	dooms::asset::ShaderAsset* const gBufferDrawerShader = dooms::assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::SHADER>("GbufferDrawer.glsl");
	mGbufferDrawerMaterial.SetShaderAsset(gBufferDrawerShader);
}
