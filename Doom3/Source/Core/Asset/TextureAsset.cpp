

#include "TextureAsset.h"


#include "../Graphics/Texture/TextureView.h"

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
	mMipMapLevelCount = cmp_MipSet.m_nMipLevels;

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

dooms::asset::TextureAsset::TextureAsset
(
	dooms::graphics::GraphicsAPI::eTargetTexture targetTexture,
	dooms::graphics::GraphicsAPI::eTextureInternalFormat internalFormat,
	dooms::graphics::GraphicsAPI::eTextureCompressedInternalFormat compressedInternalFormat, 
	UINT32 width,
	UINT32 height, 
	dooms::graphics::GraphicsAPI::eTextureComponentFormat format,
	dooms::graphics::GraphicsAPI::eDataType dataType,
	dooms::graphics::GraphicsAPI::eBindFlag resourceBindFlag,
	const void* data,
	const size_t dataSize
)
	:
	mTargetTexture(targetTexture),
	mScratchImage(),
	mWidth(width),
	mHeight(height),
	mMipMapLevelCount(1),
	mComponentFormat(format),
	mInternalFormat(internalFormat),
	mCompressedInternalFormat(compressedInternalFormat),
	mTextureResourceObject(),
	mDataType(dataType),
	mTextureData( 1, data ),
	mEntireImageSize(dataSize),
	mBindFlags(resourceBindFlag)
{
}

dooms::asset::TextureAsset::TextureAsset(std::unique_ptr<DirectX::ScratchImage>&& scratchImage, dooms::graphics::GraphicsAPI::eBindFlag resourceBindFlag)
	: mBindFlags(resourceBindFlag)
{
	SetScratchImage(std::move(scratchImage), resourceBindFlag);
}

void dooms::asset::TextureAsset::SetScratchImage(std::unique_ptr<DirectX::ScratchImage>&& scratchImage, const dooms::graphics::GraphicsAPI::eBindFlag resourceBindFlag)
{
	mScratchImage = std::move(scratchImage);
	mMipMapLevelCount = static_cast<INT32>(mScratchImage->GetMetadata().mipLevels);
	mBindFlags = resourceBindFlag;
	mDataType = graphics::GraphicsAPI::eDataType::UNSIGNED_BYTE;

	switch (mScratchImage->GetMetadata().format)
	{
	case DXGI_FORMAT::DXGI_FORMAT_BC4_UNORM:
		mTargetTexture = graphics::GraphicsAPI::eTargetTexture::TARGET_TEXTURE_TEXTURE_2D;
		mComponentFormat = graphics::GraphicsAPI::eTextureComponentFormat::TEXTURE_COMPONENT_RED;
		mInternalFormat = graphics::GraphicsAPI::eTextureInternalFormat::TEXTURE_INTERNAL_FORMAT_NONE;
		mCompressedInternalFormat = graphics::GraphicsAPI::eTextureCompressedInternalFormat::COMPRESSED_RED_RGTC1_EXT;
		break;

	case DXGI_FORMAT::DXGI_FORMAT_BC5_UNORM:
		mTargetTexture = graphics::GraphicsAPI::eTargetTexture::TARGET_TEXTURE_TEXTURE_2D;
		mComponentFormat = graphics::GraphicsAPI::eTextureComponentFormat::TEXTURE_COMPONENT_RG;
		mInternalFormat = graphics::GraphicsAPI::eTextureInternalFormat::TEXTURE_INTERNAL_FORMAT_NONE;
		mCompressedInternalFormat = graphics::GraphicsAPI::eTextureCompressedInternalFormat::COMPRESSED_RED_GREEN_RGTC2_EXT;
		break;

	case DXGI_FORMAT::DXGI_FORMAT_BC1_UNORM:
		mTargetTexture = graphics::GraphicsAPI::eTargetTexture::TARGET_TEXTURE_TEXTURE_2D;
		mComponentFormat = graphics::GraphicsAPI::eTextureComponentFormat::TEXTURE_COMPONENT_RGB;
		mInternalFormat = graphics::GraphicsAPI::eTextureInternalFormat::TEXTURE_INTERNAL_FORMAT_NONE;
		mCompressedInternalFormat = graphics::GraphicsAPI::eTextureCompressedInternalFormat::COMPRESSED_RGB_S3TC_DXT1_EXT;
		break;

	case DXGI_FORMAT::DXGI_FORMAT_BC3_UNORM:
		mTargetTexture = graphics::GraphicsAPI::eTargetTexture::TARGET_TEXTURE_TEXTURE_2D;
		mComponentFormat = graphics::GraphicsAPI::eTextureComponentFormat::TEXTURE_COMPONENT_RGBA;
		mInternalFormat = graphics::GraphicsAPI::eTextureInternalFormat::TEXTURE_INTERNAL_FORMAT_NONE;
		mCompressedInternalFormat = graphics::GraphicsAPI::eTextureCompressedInternalFormat::COMPRESSED_RGBA_S3TC_DXT5_EXT;
		break;


	default:
		D_DEBUG_LOG(eLogType::D_ERROR, "Worng Texture Format, We Only Support Compressed Type");
		NEVER_HAPPEN;
	}

	mTextureData.reserve(mScratchImage->GetImageCount());
	mWidth.reserve(mScratchImage->GetImageCount());
	mHeight.reserve(mScratchImage->GetImageCount());
	mRowByteSizes.reserve(mScratchImage->GetImageCount());
	mTotalDataSize.reserve(mScratchImage->GetImageCount());
	
	for(size_t imgIndex = 0 ; imgIndex < mScratchImage->GetImageCount() ; imgIndex++)
	{
		const Image* const img = mScratchImage->GetImage(imgIndex, 0, 0);

		mTextureData.push_back(img->pixels);
		mWidth.push_back(static_cast<INT32>(img->width));
		mHeight.push_back(static_cast<INT32>(img->height));
		mRowByteSizes.push_back(img->rowPitch);
		mTotalDataSize.push_back(img->slicePitch);
	}

	//delete scratchImage;
}

dooms::asset::TextureAsset::TextureAsset(TextureAsset&& textureAsset) noexcept
	:
		mTargetTexture(textureAsset.mTargetTexture),
		mScratchImage(std::move(textureAsset.mScratchImage)),
		mWidth(textureAsset.mWidth),
		mHeight(textureAsset.mHeight),
		mMipMapLevelCount(textureAsset.mMipMapLevelCount),
		mEntireImageSize(textureAsset.mEntireImageSize),
		mComponentFormat(textureAsset.mComponentFormat),
		mInternalFormat(textureAsset.mInternalFormat),
		mCompressedInternalFormat(textureAsset.mCompressedInternalFormat),
		mTextureResourceObject(std::move(textureAsset.mTextureResourceObject)),
		mDataType(textureAsset.mDataType),
		mTextureData(std::move(textureAsset.mTextureData)),
		mBindFlags(textureAsset.mBindFlags)
{
}

dooms::asset::TextureAsset& dooms::asset::TextureAsset::operator=(TextureAsset&& textureAsset) noexcept
{
	mTargetTexture = textureAsset.mTargetTexture;
	mScratchImage = std::move(textureAsset.mScratchImage);
	mWidth = textureAsset.mWidth;
	mHeight = textureAsset.mHeight;
	mMipMapLevelCount = textureAsset.mMipMapLevelCount;
	mEntireImageSize = textureAsset.mEntireImageSize;
	mComponentFormat = textureAsset.mComponentFormat;
	mInternalFormat = textureAsset.mInternalFormat;
	mCompressedInternalFormat = textureAsset.mCompressedInternalFormat;
	mTextureResourceObject = std::move(textureAsset.mTextureResourceObject);
	mDataType = textureAsset.mDataType;
	mTextureData = std::move(textureAsset.mTextureData);
	mBindFlags = textureAsset.mBindFlags;

	return *this;
}


dooms::asset::TextureAsset::~TextureAsset()
{
	DestroyTextureResourceObject();
}

void dooms::asset::TextureAsset::OnSetPendingKill()
{
	Asset::OnSetPendingKill();

	DestroyTextureResourceObject();
}

void dooms::asset::TextureAsset::OnEndImportInMainThread_Internal()
{
	D_START_PROFILING(Postprocess_Texture, eProfileLayers::Rendering);
	AllocateTextureResourceObject();
	D_END_PROFILING(Postprocess_Texture);
}

TextureView* dooms::asset::TextureAsset::GenerateTextureViewObject()
{
	return dooms::CreateDObject<dooms::graphics::TextureView>(this);
}

void dooms::asset::TextureAsset::AllocateTextureResourceObject()
{
	D_ASSERT(mMipMapLevelCount > 0);
	D_ASSERT(mWidth.size() > 0);
	D_ASSERT(mHeight.size() > 0);
	D_ASSERT(mRowByteSizes.size() > 0);
	D_ASSERT(mTotalDataSize.size() > 0);
	D_ASSERT(mInternalFormat != GraphicsAPI::eTextureInternalFormat::TEXTURE_INTERNAL_FORMAT_NONE || mCompressedInternalFormat != GraphicsAPI::eTextureCompressedInternalFormat::TEXTURE_COMPRESSED_INTERNAL_FORMAT_NONE);

	mTextureResourceObject = GraphicsAPI::Allocate2DTextureObject(dooms::graphics::GraphicsAPI::eTextureBindTarget::TEXTURE_2D, mMipMapLevelCount, mInternalFormat, mCompressedInternalFormat, mWidth[0], mHeight[0], mBindFlags);

	for (UINT32 mipLevelIndex = 0; mipLevelIndex < mTextureData.size(); mipLevelIndex++)
	{
		GraphicsAPI::UploadPixelsTo2DTexture(mTextureResourceObject, dooms::graphics::GraphicsAPI::eTextureBindTarget::TEXTURE_2D, mTargetTexture, mipLevelIndex, 0, 0, mWidth[mipLevelIndex], mHeight[mipLevelIndex], mComponentFormat, mDataType, mTextureData[mipLevelIndex], mRowByteSizes[mipLevelIndex], mTotalDataSize[mipLevelIndex]);
	}
}

void dooms::asset::TextureAsset::DestroyTextureResourceObject()
{
	GraphicsAPI::DestroyTextureObject(mTextureResourceObject);
}

dooms::asset::eAssetType dooms::asset::TextureAsset::GetEAssetType() const
{
	return dooms::asset::eAssetType::TEXTURE;
}

dooms::graphics::BufferID dooms::asset::TextureAsset::GetTextureResourceObject()
{
	return mTextureResourceObject;
}

GraphicsAPI::eTextureComponentFormat dooms::asset::TextureAsset::GetTextureComponentFormat() const
{
	return mComponentFormat;
}

GraphicsAPI::eTextureInternalFormat dooms::asset::TextureAsset::GetTextureInternalFormat() const
{
	return mInternalFormat;
}

GraphicsAPI::eTextureCompressedInternalFormat dooms::asset::TextureAsset::GetTextureCompressedInternalFormat() const
{
	return mCompressedInternalFormat;
}

UINT32 dooms::asset::TextureAsset::GetTextureWidth(const size_t mipLevelIndex) const
{
	D_ASSERT(mipLevelIndex < mWidth.size());
	return mWidth[mipLevelIndex];
}

UINT32 dooms::asset::TextureAsset::GetTextureHeight(const size_t mipLevelIndex) const
{
	D_ASSERT(mipLevelIndex < mHeight.size());
	return mHeight[mipLevelIndex];
}

UINT32 dooms::asset::TextureAsset::GetMipMapLevel() const
{
	return mMipMapLevelCount;
}

UINT64 dooms::asset::TextureAsset::GetEntireImageSize() const
{
	return mEntireImageSize;
}

GraphicsAPI::eDataType dooms::asset::TextureAsset::GetTextureDataType() const
{
	return dooms::graphics::GraphicsAPI::eDataType::UNSIGNED_BYTE;
}

dooms::graphics::TextureView* dooms::asset::TextureAsset::GetTextureView()
{
	return dooms::CreateDObject<dooms::graphics::TextureView>()
}

