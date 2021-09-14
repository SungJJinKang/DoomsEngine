#include "PicktureInPickture.h"
#include "Game/AssetManager/AssetManager.h"



doom::graphics::PicktureInPickture::PicktureInPickture(const math::Vector2& leftBottomNDCPoint, const math::Vector2& rightTopNDCPoint, SingleTexture* const _drawedTexture)
	:mPlaneMesh{ Mesh::GetQuadMesh(leftBottomNDCPoint, rightTopNDCPoint) }, mDrawedTexture(_drawedTexture)
{
}

void doom::graphics::PicktureInPickture::SetTexture(SingleTexture* const texture)
{
	mDrawedTexture = texture;
}



void doom::graphics::PicktureInPickture::DrawPictureInPicture()
{
	PicktureInPickture::mPIPMaterial.UseProgram();
	mDrawedTexture->ActiveTexture(0);
	mDrawedTexture->BindTexture();
	mPlaneMesh.Draw();
}

