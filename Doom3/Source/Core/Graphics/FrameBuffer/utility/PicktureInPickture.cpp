#include "PicktureInPickture.h"
#include "Game/AssetManager/AssetManager.h"

doom::graphics::PicktureInPickture::PicktureInPickture(int textureWidth, int textureHeight, const math::Vector2& leftBottomNDCPoint, const math::Vector2& rightTopNDCPoint)
	:mMesh{ Mesh::GetQuadMesh(leftBottomNDCPoint, rightTopNDCPoint) }
{
	if (PicktureInPickture::mPIPMaterial.IsGenerated() == false)
	{
		auto pipMaterial = doom::assetimporter::AssetManager::GetAsset<asset::eAssetType::SHADER>("Default2DTextureShader.glsl");
		PicktureInPickture::mPIPMaterial.SetShaderAsset(pipMaterial);
	}

	mFrameBuffer.GenerateBuffer(textureWidth, textureHeight);
	mScreenTexture = &(mFrameBuffer.AttachTextureBuffer(GraphicsAPI::eBufferType::COLOR, textureWidth, textureHeight));
	mFrameBuffer.AttachRenderBuffer(GraphicsAPI::eBufferType::DEPTH, textureWidth, textureHeight);

}

void doom::graphics::PicktureInPickture::BindFrameBuffer()
{
	mFrameBuffer.BindFrameBuffer();
}

void doom::graphics::PicktureInPickture::UnBindFrameBuffer()
{
	mFrameBuffer.UnBindFrameBuffer();
}

void doom::graphics::PicktureInPickture::RevertFrameBuffer()
{
	mFrameBuffer.RevertFrameBuffer();
}

void doom::graphics::PicktureInPickture::DrawPictureInPicture()
{
	PicktureInPickture::mPIPMaterial.UseProgram();
	mScreenTexture->ActiveTexture(0);
	mScreenTexture->BindTexture();
	mMesh.Draw();
}

void doom::graphics::PicktureInPickture::ClearFrameBuffer()
{
	mFrameBuffer.Clear();
}
