

#include "TextureAsset.h"


#include "../Graphics/Texture/Texture.h"
#include "../Graphics/Texture/SingleTexture.h"

#include <DirectXTex.h>

using namespace doom::graphics;
using namespace DirectX;
/*
doom::asset::TextureAsset::TextureAsset(int width, int height, int componentCount, unsigned char* data, eTextureCompressionType compressionType)
	: mNearWidth{ width }, mNearHeight{ height }, mDataComponentFormat{ static_cast<eTextureComponent>(componentCount) }, mTexturerCompressionType{ compressionType }, mData{ data }
{

}


doom::asset::TextureAsset::TextureAsset()
{
	mNearWidth = cmp_MipSet.m_nWidth;
	mNearHeight = cmp_MipSet.m_nHeight;
	mMipMapLevel = cmp_MipSet.m_nMipLevels;

	bmIsCompressed = cmp_MipSet.m_compressed;

	mInternalFormat; // 1 ~ 4 ( rgb, rgba ~~ )
	mComponentFormat; // 1 ~ 4 ( rgb, rgba ~~ )
	mCompressedInternalFormat;

	switch (cmp_MipSet.m_format)
	{
	case CMP_FORMAT::CMP_FORMAT_DXT5:
		mCompressedInternalFormat = graphics::eTextureCompressedInternalFormat::COMPRESSED_RGBA_S3TC_DXT5_EXT;
		mComponentFormat = graphics::eTextureComponentFormat::RGBA;
		bmIsCompressed = true;
		break;
	case  CMP_FORMAT::CMP_FORMAT_DXT1:
		mCompressedInternalFormat = graphics::eTextureCompressedInternalFormat::COMPRESSED_RGB_S3TC_DXT1_EXT; // we don't support DXT1 with alpha
		mComponentFormat = graphics::eTextureComponentFormat::RGB;
		bmIsCompressed = true;
		break;

	case  CMP_FORMAT::CMP_FORMAT_BC4:
		mInternalFormat = graphics::eTextureInternalFormat::COMPRESSED_RED_RGTC1;
		mComponentFormat = graphics::eTextureComponentFormat::RG;
		bmIsCompressed = false;
		break;

	case  CMP_FORMAT::CMP_FORMAT_BC5:
		mInternalFormat = graphics::eTextureInternalFormat::COMPRESSED_RG_RGTC2;
		mComponentFormat = graphics::eTextureComponentFormat::RED;
		bmIsCompressed = false;
		break;

	default:
		NEVER_HAPPEN;
	}
	
}
*/

doom::asset::TextureAsset::TextureAsset() = default;

void doom::asset::TextureAsset::SetScratchImage(std::unique_ptr<DirectX::ScratchImage>&& scratchImage)
{
	mScratchImage = std::move(scratchImage);
	mWidth = static_cast<int>(mScratchImage->GetMetadata().width);
	mHeight = static_cast<int>(mScratchImage->GetMetadata().height);
	mMipMapLevel = static_cast<int>(mScratchImage->GetMetadata().mipLevels);

	switch (mScratchImage->GetMetadata().format)
	{
	case DXGI_FORMAT::DXGI_FORMAT_BC4_UNORM:
		mComponentFormat = graphics::eTextureComponentFormat::RED;
		mInternalFormat = graphics::eTextureInternalFormat::NONE;
		mCompressedInternalFormat = graphics::eTextureCompressedInternalFormat::COMPRESSED_RED_RGTC1_EXT;
		bmIsCompressed = true;
		break;

	case DXGI_FORMAT::DXGI_FORMAT_BC5_UNORM:
		mComponentFormat = graphics::eTextureComponentFormat::RG;
		mInternalFormat = graphics::eTextureInternalFormat::NONE;
		mCompressedInternalFormat = graphics::eTextureCompressedInternalFormat::COMPRESSED_RED_GREEN_RGTC2_EXT;
		bmIsCompressed = true;
		break;

	case DXGI_FORMAT::DXGI_FORMAT_BC1_UNORM:
		mComponentFormat = graphics::eTextureComponentFormat::RGB;
		mInternalFormat = graphics::eTextureInternalFormat::NONE;
		mCompressedInternalFormat = graphics::eTextureCompressedInternalFormat::COMPRESSED_RGB_S3TC_DXT1_EXT;
		bmIsCompressed = true;
		break;

	case DXGI_FORMAT::DXGI_FORMAT_BC3_UNORM:
		mComponentFormat = graphics::eTextureComponentFormat::RGBA;
		mInternalFormat = graphics::eTextureInternalFormat::NONE;
		mCompressedInternalFormat = graphics::eTextureCompressedInternalFormat::COMPRESSED_RGBA_S3TC_DXT5_EXT;
		bmIsCompressed = true;
		break;


	default:
		D_DEBUG_LOG("Worng Texture Format, We Only Support Compressed Type", eLogType::D_ERROR);
		NEVER_HAPPEN;
	}

	//delete scratchImage;
}

doom::asset::TextureAsset::TextureAsset(TextureAsset&& textureAsset) noexcept = default;
doom::asset::TextureAsset& doom::asset::TextureAsset::operator=(TextureAsset&& textureAsset) noexcept = default;
doom::asset::TextureAsset::~TextureAsset() = default;

void doom::asset::TextureAsset::OnEndImportInMainThread_Internal()
{
	D_START_PROFILING(Postprocess_Texture, eProfileLayers::Rendering);
	CreateTexture();
	D_END_PROFILING(Postprocess_Texture);
}

Texture* doom::asset::TextureAsset::GetTexture() const
{
	return mTexture;
}

doom::asset::eAssetType doom::asset::TextureAsset::GetEAssetType() const
{
	return doom::asset::eAssetType::TEXTURE;
}

void doom::asset::TextureAsset::CreateTexture()
{
	D_ASSERT(mScratchImage->GetImageCount() != 0);
	std::vector<const DirectX::Image*> mipmapPixels{};
	for (unsigned int i = 0; i < mScratchImage->GetImageCount(); i++)
	{
		//https://github.com/microsoft/DirectXTex/blob/master/DirectXTex/DirectXTexImage.cpp
		mipmapPixels.push_back(mScratchImage->GetImage(i, 0, 0));
	}

	D_ASSERT(mInternalFormat != eTextureInternalFormat::NONE || mCompressedInternalFormat != eTextureCompressedInternalFormat::NONE);
	if (mInternalFormat != eTextureInternalFormat::NONE)
	{
		mTexture =
			new graphics::SingleTexture(Texture::eTextureType::DIFFUSE, Texture::eTargetTexture::TEXTURE_2D, mInternalFormat, mWidth, mHeight, mComponentFormat, Texture::eDataType::UNSIGNED_BYTE, mipmapPixels);

	}
	else if (mCompressedInternalFormat != eTextureCompressedInternalFormat::NONE)
	{
		mTexture =
			new graphics::SingleTexture(Texture::eTextureType::DIFFUSE, Texture::eTargetTexture::TEXTURE_2D, mCompressedInternalFormat, mWidth, mHeight, mComponentFormat, Texture::eDataType::UNSIGNED_BYTE, mipmapPixels);
	}
	if (mScratchImage)
	{
		mScratchImage.reset();
	}

}

