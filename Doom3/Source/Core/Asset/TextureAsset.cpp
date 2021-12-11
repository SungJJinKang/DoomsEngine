

#include "TextureAsset.h"


#include "../Graphics/Texture/Texture.h"
#include "../Graphics/Texture/SingleTexture.h"

#include <DirectXTex.h>

using namespace dooms::graphics;
using namespace DirectX;
/*
dooms::asset::TextureAsset::TextureAsset(INT32 width, INT32 height, INT32 componentCount, unsigned char* data, eTextureCompressionType compressionType)
	: mNearWidth{ width }, mNearHeight{ height }, mDataComponentFormat{ static_cast<eTextureComponent>(componentCount) }, mTexturerCompressionType{ compressionType }, mID{ data }
{

}


dooms::asset::TextureAsset::TextureAsset()
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

dooms::asset::TextureAsset::TextureAsset() = default;

void dooms::asset::TextureAsset::SetScratchImage(std::unique_ptr<DirectX::ScratchImage>&& scratchImage)
{
	mScratchImage = std::move(scratchImage);
	mWidth = static_cast<INT32>(mScratchImage->GetMetadata().width);
	mHeight = static_cast<INT32>(mScratchImage->GetMetadata().height);
	mMipMapLevel = static_cast<INT32>(mScratchImage->GetMetadata().mipLevels);

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
		D_DEBUG_LOG(eLogType::D_ERROR, "Worng Texture Format, We Only Support Compressed Type");
		NEVER_HAPPEN;
	}

	//delete scratchImage;
}

dooms::asset::TextureAsset::TextureAsset(TextureAsset&& textureAsset) noexcept
	: mScratchImage(std::move(textureAsset.mScratchImage)), mWidth(textureAsset.mWidth), mHeight(textureAsset.mHeight),
      mMipMapLevel(textureAsset.mMipMapLevel), mEntireImageSize(textureAsset.mEntireImageSize), bmIsCompressed(textureAsset.bmIsCompressed),
	  mComponentFormat(textureAsset.mComponentFormat), mInternalFormat(textureAsset.mInternalFormat),
	  mCompressedInternalFormat(textureAsset.mCompressedInternalFormat), mDefaultTextureObject(textureAsset.mDefaultTextureObject)
{
	textureAsset.mDefaultTextureObject = nullptr;
}

dooms::asset::TextureAsset& dooms::asset::TextureAsset::operator=(TextureAsset&& textureAsset) noexcept
{
	mScratchImage = std::move(textureAsset.mScratchImage);
	mWidth = textureAsset.mWidth;
	mHeight = textureAsset.mHeight;
	mMipMapLevel = textureAsset.mMipMapLevel;
	mEntireImageSize = textureAsset.mEntireImageSize;
	bmIsCompressed = textureAsset.bmIsCompressed;
	mComponentFormat = textureAsset.mComponentFormat;
	mInternalFormat = textureAsset.mInternalFormat;
	mCompressedInternalFormat = textureAsset.mCompressedInternalFormat;
	mDefaultTextureObject = textureAsset.mDefaultTextureObject;


	textureAsset.mDefaultTextureObject = nullptr;

	return *this;
}

void dooms::asset::TextureAsset::DestroyDefaultTextureObject()
{
	if(dooms::IsLowLevelValid(mDefaultTextureObject) == true)
	{
		mDefaultTextureObject->SetIsPendingKill();
	}
}

dooms::asset::TextureAsset::~TextureAsset()
{
}

void dooms::asset::TextureAsset::OnSetPendingKill()
{
	Asset::OnSetPendingKill();

	DestroyDefaultTextureObject();
}

void dooms::asset::TextureAsset::OnEndImportInMainThread_Internal()
{
	D_START_PROFILING(Postprocess_Texture, eProfileLayers::Rendering);
	CreateDefaultTexture();
	D_END_PROFILING(Postprocess_Texture);
}

const Texture* dooms::asset::TextureAsset::GetDefaultTextureObject() const
{
	D_ASSERT(IsValid(mDefaultTextureObject));
	return mDefaultTextureObject;
}

Texture* dooms::asset::TextureAsset::CreateTextureObject()
{
	Texture* createdTexture = nullptr;

	D_ASSERT(mScratchImage->GetImageCount() != 0);
	std::vector<const DirectX::Image*> mipmapPixels{};
	for (UINT32 i = 0; i < mScratchImage->GetImageCount(); i++)
	{
		//https://github.com/microsoft/DirectXTex/blob/master/DirectXTex/DirectXTexImage.cpp
		mipmapPixels.push_back(mScratchImage->GetImage(i, 0, 0));
	}

	D_ASSERT(mInternalFormat != eTextureInternalFormat::NONE || mCompressedInternalFormat != eTextureCompressedInternalFormat::NONE);
	if (mInternalFormat != eTextureInternalFormat::NONE)
	{
		createdTexture = dooms::CreateDObject<dooms::graphics::SingleTexture>(
			Texture::eTextureType::DIFFUSE, Texture::eTargetTexture::TEXTURE_2D, 
			mInternalFormat, mWidth, mHeight, mComponentFormat, 
			Texture::eDataType::UNSIGNED_BYTE, mipmapPixels
			);
	}
	else if (mCompressedInternalFormat != eTextureCompressedInternalFormat::NONE)
	{
		createdTexture = dooms::CreateDObject<dooms::graphics::SingleTexture>(
			Texture::eTextureType::DIFFUSE, Texture::eTargetTexture::TEXTURE_2D, 
			mCompressedInternalFormat, mWidth, mHeight, mComponentFormat, 
			Texture::eDataType::UNSIGNED_BYTE, mipmapPixels
			);
	}

	D_ASSERT(createdTexture != nullptr);
	return createdTexture;
}

dooms::asset::eAssetType dooms::asset::TextureAsset::GetEAssetType() const
{
	return dooms::asset::eAssetType::TEXTURE;
}

void dooms::asset::TextureAsset::CreateDefaultTexture()
{
	D_ASSERT(mScratchImage->GetImageCount() != 0);
	
	mDefaultTextureObject = CreateTextureObject();
}

