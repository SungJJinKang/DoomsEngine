#include "PicktureInPickture.h"

#include "Game/AssetManager/AssetManager.h"
#include "../Texture/SingleTexture.h"


void dooms::graphics::PicktureInPickture::InitializeDefaultPIPMaterial()
{
	if (PicktureInPickture::mDefualtPIPMaterial.IsGenerated() == false)
	{
		dooms::asset::ShaderAsset* const pipMaterial = dooms::assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::SHADER>("Default2DTextureShader.glsl");
		PicktureInPickture::mDefualtPIPMaterial.SetShaderAsset(pipMaterial);
	}

	
}

dooms::graphics::PicktureInPickture::PicktureInPickture()
{
}

void dooms::graphics::PicktureInPickture::SetDefaultPIPMaterial()
{
	InitializeDefaultPIPMaterial();
	mPIPMaterial = &(PicktureInPickture::mDefualtPIPMaterial);
}

dooms::graphics::PicktureInPickture::PicktureInPickture(const math::Vector2& leftBottomNDCPoint, const math::Vector2& rightTopNDCPoint, SingleTexture* const _drawedTexture)
	:mPlaneMesh{ Mesh::GetQuadMesh(leftBottomNDCPoint, rightTopNDCPoint) }, mDrawedTexture(_drawedTexture), mPIPMaterial(nullptr), bmIsDrawOnScreen(true)
{
	SetDefaultPIPMaterial();
}

dooms::graphics::PicktureInPickture::PicktureInPickture(const math::Vector2& leftBottomNDCPoint, const math::Vector2& rightTopNDCPoint, SingleTexture* const _drawedTexture, Material* const _pipMaterial)
	:mPlaneMesh{ Mesh::GetQuadMesh(leftBottomNDCPoint, rightTopNDCPoint) }, mDrawedTexture(_drawedTexture), mPIPMaterial(_pipMaterial), bmIsDrawOnScreen(true)
{
	
}

/*dooms::graphics::PicktureInPickture& dooms::graphics::PicktureInPickture::operator=
(
	const math::Vector2& leftBottomNDCPoint, 
	const math::Vector2& rightTopNDCPoint, 
	SingleTexture* const _drawedTexture
	)
{
	mPlaneMesh = Mesh::GetQuadMesh(leftBottomNDCPoint, rightTopNDCPoint);
	mDrawedTexture = _drawedTexture;
	SetDefaultPIPMaterial();
	bmIsDrawOnScreen = true;
}

dooms::graphics::PicktureInPickture& dooms::graphics::PicktureInPickture::operator=
(
	const math::Vector2& leftBottomNDCPoint, 
	const math::Vector2& rightTopNDCPoint, 
	SingleTexture* const _drawedTexture,
	Material* const _pipMaterial
	)
{
	mPlaneMesh = Mesh::GetQuadMesh(leftBottomNDCPoint, rightTopNDCPoint);
	mDrawedTexture = _drawedTexture;
	mPIPMaterial = _pipMaterial;
	bmIsDrawOnScreen = true;
}*/

dooms::graphics::PicktureInPickture::~PicktureInPickture()
{
}

void dooms::graphics::PicktureInPickture::SetTexture(SingleTexture* const texture)
{
	mDrawedTexture = texture;
}

void dooms::graphics::PicktureInPickture::SetMaterial(Material* const _pipMaterial)
{
	mPIPMaterial = _pipMaterial;
}

void dooms::graphics::PicktureInPickture::DrawPictureInPicture()
{
	if (bmIsDrawOnScreen == true)
	{
		if (mDrawedTexture != nullptr && mPIPMaterial != nullptr)
		{
			mPIPMaterial->UseProgram();
			mDrawedTexture->ActiveTexture(0);
			mDrawedTexture->BindTexture();
			mPlaneMesh.Draw();

		}
		else
		{
			D_DEBUG_LOG(eLogType::D_ERROR, "Plase Set Texture of PIP");
		}
	}
	
	
}

