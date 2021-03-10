

#include "TextureAsset.h"


#include "../Graphics/Texture/Texture.h"
#include "../Graphics/Texture/SingleTexture.h"

#include <DirectXTex.h>

using namespace doom::graphics;
using namespace DirectX;
/*
doom::asset::TextureAsset::TextureAsset(int width, int height, int componentCount, unsigned char* data, eTextureCompressionType compressionType)
	: mWidth{ width }, mHeight{ height }, mDataComponentFormat{ static_cast<eTextureComponent>(componentCount) }, mTexturerCompressionType{ compressionType }, mData{ data }
{

}


doom::asset::TextureAsset::TextureAsset()
{
	this->mWidth = cmp_MipSet.m_nWidth;
	this->mHeight = cmp_MipSet.m_nHeight;
	this->mMipMapLevel = cmp_MipSet.m_nMipLevels;

	this->bmIsCompressed = cmp_MipSet.m_compressed;

	this->mInternalFormat; // 1 ~ 4 ( rgb, rgba ~~ )
	this->mComponentFormat; // 1 ~ 4 ( rgb, rgba ~~ )
	this->mCompressedInternalFormat;

	switch (cmp_MipSet.m_format)
	{
	case CMP_FORMAT::CMP_FORMAT_DXT5:
		mCompressedInternalFormat = graphics::eTextureCompressedInternalFormat::COMPRESSED_RGBA_S3TC_DXT5_EXT;
		mComponentFormat = graphics::eTextureComponentFormat::RGBA;
		this->bmIsCompressed = true;
		break;
	case  CMP_FORMAT::CMP_FORMAT_DXT1:
		mCompressedInternalFormat = graphics::eTextureCompressedInternalFormat::COMPRESSED_RGB_S3TC_DXT1_EXT; // we don't support DXT1 with alpha
		mComponentFormat = graphics::eTextureComponentFormat::RGB;
		this->bmIsCompressed = true;
		break;

	case  CMP_FORMAT::CMP_FORMAT_BC4:
		mInternalFormat = graphics::eTextureInternalFormat::COMPRESSED_RED_RGTC1;
		mComponentFormat = graphics::eTextureComponentFormat::RG;
		this->bmIsCompressed = false;
		break;

	case  CMP_FORMAT::CMP_FORMAT_BC5:
		mInternalFormat = graphics::eTextureInternalFormat::COMPRESSED_RG_RGTC2;
		mComponentFormat = graphics::eTextureComponentFormat::RED;
		this->bmIsCompressed = false;
		break;

	default:
		NEVER_HAPPEN;
	}
	
}
*/
void doom::asset::TextureAsset::SetScratchImage(std::unique_ptr<DirectX::ScratchImage>&& scratchImage)
{
	this->mScratchImage = std::move(scratchImage);
	this->mWidth = static_cast<int>(mScratchImage->GetMetadata().width);
	this->mHeight = static_cast<int>(mScratchImage->GetMetadata().height);
	this->mMipMapLevel = static_cast<int>(mScratchImage->GetMetadata().mipLevels);

	switch (mScratchImage->GetMetadata().format)
	{
	case DXGI_FORMAT::DXGI_FORMAT_BC4_UNORM:
		this->mComponentFormat = graphics::eTextureComponentFormat::RED;
		this->mInternalFormat = graphics::eTextureInternalFormat::NONE;
		this->mCompressedInternalFormat = graphics::eTextureCompressedInternalFormat::COMPRESSED_RED_RGTC1_EXT;
		this->bmIsCompressed = true;
		break;

	case DXGI_FORMAT::DXGI_FORMAT_BC5_UNORM:
		this->mComponentFormat = graphics::eTextureComponentFormat::RG;
		this->mInternalFormat = graphics::eTextureInternalFormat::NONE;
		this->mCompressedInternalFormat = graphics::eTextureCompressedInternalFormat::COMPRESSED_RED_GREEN_RGTC2_EXT;
		bmIsCompressed = true;
		break;

	case DXGI_FORMAT::DXGI_FORMAT_BC1_UNORM:
		this->mComponentFormat = graphics::eTextureComponentFormat::RGB;
		this->mInternalFormat = graphics::eTextureInternalFormat::NONE;
		this->mCompressedInternalFormat = graphics::eTextureCompressedInternalFormat::COMPRESSED_RGB_S3TC_DXT1_EXT;
		bmIsCompressed = true;
		break;

	case DXGI_FORMAT::DXGI_FORMAT_BC3_UNORM:
		this->mComponentFormat = graphics::eTextureComponentFormat::RGBA;
		this->mInternalFormat = graphics::eTextureInternalFormat::NONE;
		this->mCompressedInternalFormat = graphics::eTextureCompressedInternalFormat::COMPRESSED_RGBA_S3TC_DXT5_EXT;
		bmIsCompressed = true;
		break;


	default:
		D_DEBUG_LOG("Worng Texture Format, We Only Support Compressed Type", eLogType::D_ERROR);
		NEVER_HAPPEN;
	}

	//delete scratchImage;
}

void doom::asset::TextureAsset::OnEndImportInMainThread_Internal()
{
	this->CreateTexture();
}

void doom::asset::TextureAsset::CreateTexture()
{
	D_ASSERT(mScratchImage->GetImageCount() != 0);
	std::vector<const DirectX::Image*> mipmapPixels{};
	for (unsigned int i = 0; i < mScratchImage->GetImageCount(); i++)
	{
		//https://github.com/microsoft/DirectXTex/blob/master/DirectXTex/DirectXTexImage.cpp
		mipmapPixels.push_back(this->mScratchImage->GetImage(i, 0, 0));
	}

	D_ASSERT(this->mInternalFormat != eTextureInternalFormat::NONE || this->mCompressedInternalFormat != eTextureCompressedInternalFormat::NONE);
	if (this->mInternalFormat != eTextureInternalFormat::NONE)
	{
		this->mTexture =
			new graphics::SingleTexture(Texture::eTextureType::DIFFUSE, Texture::eTargetTexture::TEXTURE_2D, this->mInternalFormat, mWidth, mHeight, this->mComponentFormat, Texture::eDataType::UNSIGNED_BYTE, mipmapPixels);

	}
	else if (this->mCompressedInternalFormat != eTextureCompressedInternalFormat::NONE)
	{
		this->mTexture =
			new graphics::SingleTexture(Texture::eTextureType::DIFFUSE, Texture::eTargetTexture::TEXTURE_2D, this->mCompressedInternalFormat, mWidth, mHeight, this->mComponentFormat, Texture::eDataType::UNSIGNED_BYTE, mipmapPixels);
	}
	if (this->mScratchImage)
	{
		this->mScratchImage.reset();
	}

}