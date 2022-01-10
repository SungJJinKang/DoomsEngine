#include "PicktureInPickture.h"

#include "Game/AssetManager/AssetManager.h"
#include "../Texture/SingleTexture.h"
#include "Graphics/Buffer/MeshHelper.h"


void dooms::graphics::PicktureInPickture::InitializeDefaultPIPMaterial()
{
	if (PicktureInPickture::mDefualtPIPMaterial.IsGenerated() == false)
	{
		dooms::asset::ShaderAsset* const pipMaterial = dooms::assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::SHADER>("Default2DTextureShader.glsl");
		PicktureInPickture::mDefualtPIPMaterial.SetShaderAsset(pipMaterial);
	}

	
}

dooms::graphics::PicktureInPickture::PicktureInPickture()
	: mPlaneMesh{ nullptr }, mDrawedTexture(nullptr), mPIPMaterial(nullptr)
{
}

void dooms::graphics::PicktureInPickture::SetDefaultPIPMaterial()
{
	InitializeDefaultPIPMaterial();
	mPIPMaterial = &(PicktureInPickture::mDefualtPIPMaterial);
	D_ASSERT(IsValid(mPIPMaterial));
	D_ASSERT(mPIPMaterial->IsGenerated());
}

dooms::graphics::PicktureInPickture::PicktureInPickture(const math::Vector2& leftBottomNDCPoint, const math::Vector2& rightTopNDCPoint, SingleTexture* const _drawedTexture)
	:mPlaneMesh{ meshHelper::GetQuadMesh(leftBottomNDCPoint, rightTopNDCPoint) }, mDrawedTexture(_drawedTexture), mPIPMaterial(nullptr), bmIsDrawOnScreen(true)
{
	D_ASSERT(IsValid(mDrawedTexture));
	SetDefaultPIPMaterial();
}

dooms::graphics::PicktureInPickture::PicktureInPickture(const math::Vector2& leftBottomNDCPoint, const math::Vector2& rightTopNDCPoint, SingleTexture* const _drawedTexture, Material* const _pipMaterial)
	:mPlaneMesh{ meshHelper::GetQuadMesh(leftBottomNDCPoint, rightTopNDCPoint) }, mDrawedTexture(_drawedTexture), mPIPMaterial(_pipMaterial), bmIsDrawOnScreen(true)
{
	D_ASSERT(IsValid(mDrawedTexture));
	D_ASSERT(IsValid(mPIPMaterial));
	D_ASSERT(mPIPMaterial->IsGenerated());
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
	D_ASSERT(IsValid(texture));
	mDrawedTexture = texture;
}

void dooms::graphics::PicktureInPickture::SetMaterial(Material* const _pipMaterial)
{
	D_ASSERT(IsValid(_pipMaterial));
	D_ASSERT(_pipMaterial->IsGenerated());
	mPIPMaterial = _pipMaterial;
}

void dooms::graphics::PicktureInPickture::DrawPictureInPicture()
{
	if (bmIsDrawOnScreen == true)
	{
		D_ASSERT(IsValid(mDrawedTexture) && IsValid(mPIPMaterial));
		if (IsValid(mDrawedTexture) && IsValid(mPIPMaterial))
		{
			mPIPMaterial->UseProgram();
			mDrawedTexture->ActiveTexture(0);
			mDrawedTexture->BindTexture();
			mPlaneMesh->Draw();

		}
		else
		{
			D_DEBUG_LOG(eLogType::D_ERROR, "Plase Set Texture of PIP");
		}
	}
	
	
}

