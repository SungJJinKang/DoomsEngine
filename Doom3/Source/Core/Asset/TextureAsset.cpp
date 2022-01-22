

#include "TextureAsset.h"


#include "../Graphics/Texture/TextureView.h"

#include <DirectXTex.h>


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
	dooms::graphics::GraphicsAPI::eTextureBindTarget textureBindTarget,
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
	mBindFlags(resourceBindFlag),
	mTextureBindTarget(textureBindTarget)
{
}

dooms::asset::TextureAsset::TextureAsset(std::unique_ptr<DirectX::ScratchImage>&& scratchImage, dooms::graphics::GraphicsAPI::eBindFlag resourceBindFlag)
	: mBindFlags(resourceBindFlag)
{
	SetScratchImage(std::move(scratchImage), resourceBindFlag);
	AllocateTextureResourceObject();
}

void dooms::asset::TextureAsset::SetScratchImage(std::unique_ptr<DirectX::ScratchImage>&& scratchImage, const dooms::graphics::GraphicsAPI::eBindFlag resourceBindFlag)
{
	mScratchImage = std::move(scratchImage);
	mMipMapLevelCount = static_cast<INT32>(mScratchImage->GetMetadata().mipLevels);
	mBindFlags = resourceBindFlag;
	mDataType = graphics::GraphicsAPI::eDataType::UNSIGNED_BYTE;

	switch (mScratchImage->GetMetadata().dimension)
	{
	case DirectX::TEX_DIMENSION_TEXTURE1D:
		mTextureBindTarget = graphics::GraphicsAPI::eTextureBindTarget::TEXTURE_1D;
		break;
	case DirectX::TEX_DIMENSION_TEXTURE2D:
		mTextureBindTarget = graphics::GraphicsAPI::eTextureBindTarget::TEXTURE_2D;

		break;
	case DirectX::TEX_DIMENSION_TEXTURE3D:
		mTextureBindTarget = graphics::GraphicsAPI::eTextureBindTarget::TEXTURE_3D;

		break;
	default:
		D_ASSERT(false);
	}

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
		const DirectX::Image* const img = mScratchImage->GetImage(imgIndex, 0, 0);

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

void dooms::asset::TextureAsset::AllocateTextureResourceObject()
{
	D_ASSERT(mMipMapLevelCount > 0);
	D_ASSERT(mWidth.size() > 0);
	D_ASSERT(mHeight.size() > 0);
	D_ASSERT(mRowByteSizes.size() > 0);
	D_ASSERT(mTotalDataSize.size() > 0);
	D_ASSERT(mInternalFormat != graphics::GraphicsAPI::eTextureInternalFormat::TEXTURE_INTERNAL_FORMAT_NONE || mCompressedInternalFormat != graphics::GraphicsAPI::eTextureCompressedInternalFormat::TEXTURE_COMPRESSED_INTERNAL_FORMAT_NONE);

	mTextureResourceObject = graphics::GraphicsAPI::Allocate2DTextureObject(dooms::graphics::GraphicsAPI::eTextureBindTarget::TEXTURE_2D, mMipMapLevelCount, mInternalFormat, mCompressedInternalFormat, mWidth[0], mHeight[0], mBindFlags);

	for (UINT32 mipLevelIndex = 0; mipLevelIndex < mTextureData.size(); mipLevelIndex++)
	{
		graphics::GraphicsAPI::UploadPixelsTo2DTexture(mTextureResourceObject, dooms::graphics::GraphicsAPI::eTextureBindTarget::TEXTURE_2D, mTargetTexture, mipLevelIndex, 0, 0, mWidth[mipLevelIndex], mHeight[mipLevelIndex], mComponentFormat, mDataType, mTextureData[mipLevelIndex], mRowByteSizes[mipLevelIndex], mTotalDataSize[mipLevelIndex]);
	}
}

void dooms::asset::TextureAsset::DestroyTextureResourceObject()
{
	graphics::GraphicsAPI::DestroyTextureObject(mTextureResourceObject);
}

dooms::asset::eAssetType dooms::asset::TextureAsset::GetEAssetType() const
{
	return dooms::asset::eAssetType::TEXTURE;
}

dooms::graphics::BufferID dooms::asset::TextureAsset::GetTextureResourceObject()
{
	return mTextureResourceObject;
}

dooms::graphics::GraphicsAPI::eTextureComponentFormat dooms::asset::TextureAsset::GetTextureComponentFormat() const
{
	return mComponentFormat;
}

dooms::graphics::GraphicsAPI::eTextureInternalFormat dooms::asset::TextureAsset::GetTextureInternalFormat() const
{
	return mInternalFormat;
}

dooms::graphics::GraphicsAPI::eTextureCompressedInternalFormat dooms::asset::TextureAsset::GetTextureCompressedInternalFormat() const
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

dooms::graphics::GraphicsAPI::eDataType dooms::asset::TextureAsset::GetTextureDataType() const
{
	return dooms::graphics::GraphicsAPI::eDataType::UNSIGNED_BYTE;
}

dooms::graphics::TextureView* dooms::asset::TextureAsset::GenerateTextureView
(
	const UINT32 defaultBindingPosition,
	const graphics::GraphicsAPI::eGraphicsPipeLineStage defaultTargetGraphicsPipeLineStage
)
{
	return dooms::CreateDObject<dooms::graphics::TextureView>(this, defaultBindingPosition, defaultTargetGraphicsPipeLineStage);
}

