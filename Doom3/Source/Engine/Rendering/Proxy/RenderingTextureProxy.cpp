#include "RenderingTextureProxy.h"

dooms::graphics::RenderingTextureProxy::~RenderingTextureProxy()
{
	DestroyTextureResourceObject();
}

void dooms::graphics::RenderingTextureProxy::InitRenderingTextureProxy(FRenderingTextureProxyInitializer& Initializer)
{
	ScratchImage = std::move(Initializer.ScratchImage);
	TextureData = std::move(Initializer.TextureData);
	TargetTexture = Initializer.TargetTexture;
	TextureBindTarget = Initializer.TextureBindTarget;
	Width = std::move(Initializer.Width);
	Height = std::move(Initializer.Height);
	SrcRowPitch = std::move(Initializer.SrcDepthPitch);
	SrcDepthPitch = std::move(Initializer.SrcDepthPitch);
	MipMapLevelCount = Initializer.MipMapLevelCount;
	EntireImageSize = Initializer.EntireImageSize;
	ComponentFormat = Initializer.ComponentFormat;
	InternalFormat = Initializer.InternalFormat;
	CompressedInternalFormat = Initializer.CompressedInternalFormat;
	DataType = Initializer.DataType;
	BindFlags = Initializer.BindFlags;
}

void dooms::graphics::RenderingTextureProxy::AllocateTextureResourceObject()
{
	D_ASSERT(MipMapLevelCount > 0);
	D_ASSERT(Width.size() > 0);
	D_ASSERT(Height.size() > 0);
	D_ASSERT(TextureData.size() == GetMipMapLevel());
	D_ASSERT(InternalFormat == graphics::GraphicsAPI::eTextureInternalFormat::TEXTURE_INTERNAL_FORMAT_NONE || CompressedInternalFormat == graphics::GraphicsAPI::eTextureCompressedInternalFormat::TEXTURE_COMPRESSED_INTERNAL_FORMAT_NONE);

	TextureResourceObject = graphics::GraphicsAPI::Allocate2DTextureObject(dooms::graphics::GraphicsAPI::eTextureBindTarget::TEXTURE_2D, MipMapLevelCount, InternalFormat, CompressedInternalFormat, Width[0], Height[0], BindFlags);

	for (UINT32 mipLevelIndex = 0; mipLevelIndex < TextureData.size(); mipLevelIndex++)
	{
		if (TextureData[mipLevelIndex] != 0)
		{
			D_ASSERT(SrcRowPitch.size() > 0);
			D_ASSERT(SrcDepthPitch.size() > 0);

			graphics::GraphicsAPI::UploadPixelsTo2DTexture
			(
				TextureResourceObject,
				dooms::graphics::GraphicsAPI::eTextureBindTarget::TEXTURE_2D,
				TargetTexture,
				mipLevelIndex,
				0,
				0,
				Width[mipLevelIndex],
				Height[mipLevelIndex],
				ComponentFormat,
				DataType,
				InternalFormat,
				CompressedInternalFormat,
				TextureData[mipLevelIndex],
				SrcRowPitch[mipLevelIndex],
				SrcDepthPitch[mipLevelIndex]
			);
		}
	}
}

void dooms::graphics::RenderingTextureProxy::DestroyTextureResourceObject()
{
	if (TextureResourceObject.IsValid())
	{
		graphics::GraphicsAPI::DestroyTextureObject(TextureResourceObject);
		TextureResourceObject.Reset();
	}
}


dooms::graphics::GraphicsAPI::eTextureComponentFormat dooms::graphics::RenderingTextureProxy::GetTextureComponentFormat() const
{
	return ComponentFormat;
}

dooms::graphics::GraphicsAPI::eTextureInternalFormat dooms::graphics::RenderingTextureProxy::GetTextureInternalFormat() const
{
	return InternalFormat;
}

dooms::graphics::GraphicsAPI::eTextureCompressedInternalFormat dooms::graphics::RenderingTextureProxy::GetTextureCompressedInternalFormat() const
{
	return CompressedInternalFormat;
}

UINT32 dooms::graphics::RenderingTextureProxy::GetTextureWidth(const size_t mipLevelIndex) const
{
	D_ASSERT(mipLevelIndex < Width.size());
	return Width[mipLevelIndex];
}

UINT32 dooms::graphics::RenderingTextureProxy::GetTextureHeight(const size_t mipLevelIndex) const
{
	D_ASSERT(mipLevelIndex < Height.size());
	return Height[mipLevelIndex];
}

UINT32 dooms::graphics::RenderingTextureProxy::GetMipMapLevel() const
{
	return MipMapLevelCount;
}

UINT64 dooms::graphics::RenderingTextureProxy::GetEntireImageSize() const
{
	return EntireImageSize;
}

dooms::graphics::GraphicsAPI::eDataType dooms::graphics::RenderingTextureProxy::GetTextureDataType() const
{
	return dooms::graphics::GraphicsAPI::eDataType::UNSIGNED_BYTE;
}

dooms::graphics::TextureView* dooms::graphics::RenderingTextureProxy::GenerateTextureView
(
	const UINT32 defaultBindingPosition,
	const graphics::GraphicsAPI::eGraphicsPipeLineStage defaultTargetGraphicsPipeLineStage
) const
{
	return dooms::CreateDObject<dooms::graphics::TextureView>(this, defaultBindingPosition, defaultTargetGraphicsPipeLineStage);
}

