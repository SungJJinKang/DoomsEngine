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

void doom::graphics::DeferredRenderingDrawer::DrawDeferredRenderingQuadDrawer()
{
	mGbufferDrawerMaterial.UseProgram();

	GraphicsAPI::Disable(GraphicsAPI::eCapability::DEPTH_TEST);
	mQuadMesh->Draw();
	GraphicsAPI::Enable(GraphicsAPI::eCapability::DEPTH_TEST);
}

void doom::graphics::DeferredRenderingDrawer::SetShaderToGBufferMaterial()
{
	doom::asset::ShaderAsset* const gBufferDrawerShader = doom::assetimporter::AssetManager::GetAsset<asset::eAssetType::SHADER>("GbufferDrawer.glsl");
	mGbufferDrawerMaterial.SetShaderAsset(gBufferDrawerShader);
}
