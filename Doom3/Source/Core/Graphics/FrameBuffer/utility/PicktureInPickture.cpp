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

	this->mFrameBuffer.GenerateBuffer(textureWidth, textureHeight);
	this->mScreenTexture = &(this->mFrameBuffer.AttachTextureBuffer(GraphicsAPI::eBufferType::COLOR, textureWidth, textureHeight));
	this->mFrameBuffer.AttachRenderBuffer(GraphicsAPI::eBufferType::DEPTH, textureWidth, textureHeight);

}

void doom::graphics::PicktureInPickture::BindFrameBuffer()
{
	this->mFrameBuffer.BindFrameBuffer();
}

void doom::graphics::PicktureInPickture::UnBindFrameBuffer()
{
	this->mFrameBuffer.UnBindFrameBuffer();
}

void doom::graphics::PicktureInPickture::RevertFrameBuffer()
{
	this->mFrameBuffer.RevertFrameBuffer();
}

void doom::graphics::PicktureInPickture::DrawPictureInPicture()
{
	PicktureInPickture::mPIPMaterial.UseProgram();
	mScreenTexture->ActiveTexture(0);
	mScreenTexture->BindTexture();
	this->mMesh.Draw();
}

void doom::graphics::PicktureInPickture::ClearFrameBuffer()
{
	this->mFrameBuffer.Clear();
}
