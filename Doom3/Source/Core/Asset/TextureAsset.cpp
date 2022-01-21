

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

dooms::asset::TextureAsset::TextureAsset
(
	dooms::graphics::GraphicsAPI::eTargetTexture targetTexture,
	dooms::graphics::GraphicsAPI::eTextureInternalFormat internalFormat,
	dooms::graphics::GraphicsAPI::eTextureCompressedInternalFormat compressedInternalFormat, 
	UINT32 width,
	UINT32 height, 
	dooms::graphics::GraphicsAPI::eTextureComponentFormat format,
	dooms::graphics::GraphicsAPI::eDataType dataType, 
	const void* data,
	const size_t dataSize
)
	:
	mTargetTexture(targetTexture),
	mScratchImage(),
	mDefaultTextureViewObject(nullptr),
	mWidth(width),
	mHeight(height),
	mMipMapLevel(1),
	mComponentFormat(format),
	mInternalFormat(internalFormat),
	mCompressedInternalFormat(compressedInternalFormat),
	mTextureResourceObject(),
	mDataType(dataType),
	mTextureData(data),
	mEntireImageSize(dataSize)
{
}

void dooms::asset::TextureAsset::SetScratchImage(std::unique_ptr<DirectX::ScratchImage>&& scratchImage)
{
	mScratchImage = std::move(scratchImage);
	mWidth = static_cast<INT32>(mScratchImage->GetMetadata().width);
	mHeight = static_cast<INT32>(mScratchImage->GetMetadata().height);
	mMipMapLevel = static_cast<INT32>(mScratchImage->GetMetadata().mipLevels);

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

	//delete scratchImage;
}

dooms::asset::TextureAsset::TextureAsset(TextureAsset&& textureAsset) noexcept
	:
		mTargetTexture(textureAsset.mTargetTexture),
		mScratchImage(std::move(textureAsset.mScratchImage)),
		mDefaultTextureViewObject(textureAsset.mDefaultTextureViewObject),
		mWidth(textureAsset.mWidth),
		mHeight(textureAsset.mHeight),
		mMipMapLevel(textureAsset.mMipMapLevel),
		mEntireImageSize(textureAsset.mEntireImageSize),
		mComponentFormat(textureAsset.mComponentFormat),
		mInternalFormat(textureAsset.mInternalFormat),
		mCompressedInternalFormat(textureAsset.mCompressedInternalFormat),
		mTextureResourceObject(std::move(textureAsset.mTextureResourceObject)),
		mDataType(textureAsset.mDataType),
		mTextureData(textureAsset.mTextureData)
{
	textureAsset.mDefaultTextureViewObject = nullptr;
	textureAsset.mTextureData = nullptr;
}

dooms::asset::TextureAsset& dooms::asset::TextureAsset::operator=(TextureAsset&& textureAsset) noexcept
{
	mTargetTexture = textureAsset.mTargetTexture;
	mScratchImage = std::move(textureAsset.mScratchImage);
	mDefaultTextureViewObject = textureAsset.mDefaultTextureViewObject;
	textureAsset.mDefaultTextureViewObject = nullptr;
	mWidth = textureAsset.mWidth;
	mHeight = textureAsset.mHeight;
	mMipMapLevel = textureAsset.mMipMapLevel;
	mEntireImageSize = textureAsset.mEntireImageSize;
	mComponentFormat = textureAsset.mComponentFormat;
	mInternalFormat = textureAsset.mInternalFormat;
	mCompressedInternalFormat = textureAsset.mCompressedInternalFormat;
	mTextureResourceObject = std::move(textureAsset.mTextureResourceObject);
	mDataType = textureAsset.mDataType;
	mTextureData = textureAsset.mTextureData;
	textureAsset.mTextureData = nullptr;

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
	TextureView* createdTexture = nullptr;

	D_ASSERT(mScratchImage->GetImageCount() != 0);
	std::vector<const DirectX::Image*> mipmapPixels{};
	for (UINT32 i = 0; i < mScratchImage->GetImageCount(); i++)
	{
		//https://github.com/microsoft/DirectXTex/blob/master/DirectXTex/DirectXTexImage.cpp
		mipmapPixels.push_back(mScratchImage->GetImage(i, 0, 0));
	}

	D_ASSERT(mInternalFormat != GraphicsAPI::eTextureInternalFormat::TEXTURE_INTERNAL_FORMAT_NONE || mCompressedInternalFormat != GraphicsAPI::eTextureCompressedInternalFormat::TEXTURE_COMPRESSED_INTERNAL_FORMAT_NONE);

	mTextureResourceObject = GraphicsAPI::Allocate2DTextureObject(dooms::graphics::GraphicsAPI::eTextureBindTarget::TEXTURE_2D, mipmapPixels.size(), mInternalFormat, mCompressedInternalFormat, mipmapPixels[0]->width, mipmapPixels[0]->height);
	GraphicsAPI::UploadPixelsTo2DTexture(mTextureResourceObject, dooms::graphics::GraphicsAPI::eTextureBindTarget::TEXTURE_2D, mTargetTexture, 0, 0, 0, mWidth, mHeight, mComponentFormat, mDataType, mipmapPixels[0]->pixels);
	
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

INT32 dooms::asset::TextureAsset::GetTextureWidth() const
{
	return mWidth;
}

INT32 dooms::asset::TextureAsset::GetTextureHeight() const
{
	return mHeight;
}

INT32 dooms::asset::TextureAsset::GetMipMapLevel() const
{
	return mMipMapLevel;
}

INT32 dooms::asset::TextureAsset::GetEntireImageSize() const
{
	return mEntireImageSize;
}

GraphicsAPI::eDataType dooms::asset::TextureAsset::GetTextureDataType() const
{
	return dooms::graphics::GraphicsAPI::eDataType::UNSIGNED_BYTE;
}

dooms::graphics::TextureView* dooms::asset::TextureAsset::GetDefaultTextureViewObject()
{
	if(IsValid(mDefaultTextureViewObject) == false)
	{
		mDefaultTextureViewObject = GenerateTextureViewObject();
	}

	D_ASSERT(IsValid(mDefaultTextureViewObject) == true);
	return mDefaultTextureViewObject;
}

