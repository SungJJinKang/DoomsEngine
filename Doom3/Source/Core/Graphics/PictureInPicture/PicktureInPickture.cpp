#include "PicktureInPickture.h"

#include "Game/AssetManager/AssetManager.h"
#include "../Texture/SingleTexture.h"


doom::graphics::PicktureInPickture::PicktureInPickture(const math::Vector2& leftBottomNDCPoint, const math::Vector2& rightTopNDCPoint, SingleTexture* const _drawedTexture)
	:mPlaneMesh{ Mesh::GetQuadMesh(leftBottomNDCPoint, rightTopNDCPoint) }, mDrawedTexture(_drawedTexture)
{
	if (PicktureInPickture::mPIPMaterial.IsGenerated() == false)
	{
		doom::asset::ShaderAsset* const pipMaterial = doom::assetimporter::AssetManager::GetAsset<asset::eAssetType::SHADER>("Default2DTextureShader.glsl");
		PicktureInPickture::mPIPMaterial.SetShaderAsset(pipMaterial);
	}
}

doom::graphics::PicktureInPickture::~PicktureInPickture()
{
}

void doom::graphics::PicktureInPickture::SetTexture(SingleTexture* const texture)
{
	mDrawedTexture = texture;
}



void doom::graphics::PicktureInPickture::DrawPictureInPicture()
{
	if (mDrawedTexture != nullptr)
	{
		PicktureInPickture::mPIPMaterial.UseProgram();
		mDrawedTexture->ActiveTexture(0);
		mDrawedTexture->BindTexture();
		mPlaneMesh.Draw();
	}
	else
	{
		D_DEBUG_LOG("Plase Set Texture of PIP", eLogType::D_ERROR);
	}
	
}

