#include "DeferredRenderingDrawer.h"

#include <Asset/AssetManager/AssetManager.h>
#include <Asset/ShaderAsset.h>
#include "../Buffer/MeshHelper.h"


void dooms::graphics::DeferredRenderingDrawer::Initialize()
{
	SetShaderToGBufferMaterial();

	mQuadMesh = meshHelper::GetQuadMesh(meshHelper::GetFlipOptionBasedOnCurrentGraphicsAPI());
	
	D_ASSERT(IsValid(mQuadMesh) == true);
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
	mGbufferDrawerMaterial.BindMaterial();

	dooms::graphics::GraphicsAPI::SetDepthMask(false);
	D_ASSERT(IsValid(mQuadMesh) == true);
	mQuadMesh->Draw();
	dooms::graphics::GraphicsAPI::SetDepthMask(true);

	mGbufferDrawerMaterial.UnBindMaterial();
}

void dooms::graphics::DeferredRenderingDrawer::SetShaderToGBufferMaterial()
{
	dooms::asset::ShaderAsset* const gBufferDrawerShader = dooms::assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::SHADER>("GbufferDrawer.glsl");
	D_ASSERT(IsValid(gBufferDrawerShader) == true);
	mGbufferDrawerMaterial.SetShaderAsset(gBufferDrawerShader);
}
