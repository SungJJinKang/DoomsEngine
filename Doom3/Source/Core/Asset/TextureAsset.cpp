#include "TextureAsset.h"

#include <DirectXTex.h>
#include "ResourceManagement/Thread/RunnableThread/RenderThread.h"
#include "Rendering/Proxy/RenderingProxyManager.h"
#include "Rendering/Proxy/RenderingTextureProxy.h"

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
	TargetTexture(targetTexture),
	ScratchImage(),
	Width(1, width),
	Height(1, height),
	MipMapLevelCount(1),
	ComponentFormat(format),
	InternalFormat(internalFormat),
	CompressedInternalFormat(compressedInternalFormat),
	TextureResourceObject(),
	DataType(dataType),
	TextureData( 1, data ),
	EntireImageSize(dataSize),
	BindFlags(resourceBindFlag),
	TextureBindTarget(textureBindTarget)
{
}

dooms::asset::TextureAsset::TextureAsset(std::unique_ptr<DirectX::ScratchImage>&& scratchImage, dooms::graphics::GraphicsAPI::eBindFlag resourceBindFlag)
	: BindFlags(resourceBindFlag)
{
	SetScratchImage(std::move(scratchImage), resourceBindFlag);
}

void dooms::asset::TextureAsset::SetScratchImage(std::unique_ptr<DirectX::ScratchImage>&& scratchImage, const dooms::graphics::GraphicsAPI::eBindFlag resourceBindFlag)
{
	ScratchImage = std::move(scratchImage);
	MipMapLevelCount = static_cast<INT32>(ScratchImage->GetMetadata().mipLevels);
	BindFlags = resourceBindFlag;
	DataType = graphics::GraphicsAPI::eDataType::UNSIGNED_BYTE;

	switch (ScratchImage->GetMetadata().dimension)
	{
		case DirectX::TEX_DIMENSION_TEXTURE1D:
			TextureBindTarget = graphics::GraphicsAPI::eTextureBindTarget::TEXTURE_1D;
			break;
		case DirectX::TEX_DIMENSION_TEXTURE2D:
			TextureBindTarget = graphics::GraphicsAPI::eTextureBindTarget::TEXTURE_2D;

			break;
		case DirectX::TEX_DIMENSION_TEXTURE3D:
			TextureBindTarget = graphics::GraphicsAPI::eTextureBindTarget::TEXTURE_3D;

			break;
		default:
			D_ASSERT(false);
	}

	switch (ScratchImage->GetMetadata().format)
	{
		case DXGI_FORMAT::DXGI_FORMAT_BC4_UNORM:
			TargetTexture = graphics::GraphicsAPI::eTargetTexture::TARGET_TEXTURE_TEXTURE_2D;
			ComponentFormat = graphics::GraphicsAPI::eTextureComponentFormat::TEXTURE_COMPONENT_RED;
			InternalFormat = graphics::GraphicsAPI::eTextureInternalFormat::TEXTURE_INTERNAL_FORMAT_NONE;
			CompressedInternalFormat = graphics::GraphicsAPI::eTextureCompressedInternalFormat::COMPRESSED_RED_RGTC1_EXT;
			break;

		case DXGI_FORMAT::DXGI_FORMAT_BC5_UNORM:
			TargetTexture = graphics::GraphicsAPI::eTargetTexture::TARGET_TEXTURE_TEXTURE_2D;
			ComponentFormat = graphics::GraphicsAPI::eTextureComponentFormat::TEXTURE_COMPONENT_RG;
			InternalFormat = graphics::GraphicsAPI::eTextureInternalFormat::TEXTURE_INTERNAL_FORMAT_NONE;
			CompressedInternalFormat = graphics::GraphicsAPI::eTextureCompressedInternalFormat::COMPRESSED_RED_GREEN_RGTC2_EXT;
			break;

		case DXGI_FORMAT::DXGI_FORMAT_BC1_UNORM:
			TargetTexture = graphics::GraphicsAPI::eTargetTexture::TARGET_TEXTURE_TEXTURE_2D;
			ComponentFormat = graphics::GraphicsAPI::eTextureComponentFormat::TEXTURE_COMPONENT_RGB;
			InternalFormat = graphics::GraphicsAPI::eTextureInternalFormat::TEXTURE_INTERNAL_FORMAT_NONE;
			CompressedInternalFormat = graphics::GraphicsAPI::eTextureCompressedInternalFormat::COMPRESSED_RGB_S3TC_DXT1_EXT;
			break;

		case DXGI_FORMAT::DXGI_FORMAT_BC3_UNORM:
			TargetTexture = graphics::GraphicsAPI::eTargetTexture::TARGET_TEXTURE_TEXTURE_2D;
			ComponentFormat = graphics::GraphicsAPI::eTextureComponentFormat::TEXTURE_COMPONENT_RGBA;
			InternalFormat = graphics::GraphicsAPI::eTextureInternalFormat::TEXTURE_INTERNAL_FORMAT_NONE;
			CompressedInternalFormat = graphics::GraphicsAPI::eTextureCompressedInternalFormat::COMPRESSED_RGBA_S3TC_DXT5_EXT;
			break;


		default:
			D_DEBUG_LOG(eLogType::D_ERROR, "Worng Texture Format, We Only Support Compressed Type");
			NEVER_HAPPEN;
	}

	TextureData.reserve(ScratchImage->GetImageCount());
	Width.reserve(ScratchImage->GetImageCount());
	Height.reserve(ScratchImage->GetImageCount());
	SrcRowPitch.reserve(ScratchImage->GetImageCount());
	SrcDepthPitch.reserve(ScratchImage->GetImageCount());
	
	for(size_t imgIndex = 0 ; imgIndex < ScratchImage->GetImageCount() ; imgIndex++)
	{
		const DirectX::Image* const img = ScratchImage->GetImage(imgIndex, 0, 0);

		TextureData.push_back(img->pixels);
		Width.push_back(static_cast<INT32>(img->width));
		Height.push_back(static_cast<INT32>(img->height));
		SrcRowPitch.push_back(img->rowPitch);
		SrcDepthPitch.push_back(img->slicePitch);
	}

	//delete scratchImage;
}

dooms::asset::TextureAsset::TextureAsset(TextureAsset&& textureAsset) noexcept = default;
dooms::asset::TextureAsset& dooms::asset::TextureAsset::operator=(TextureAsset&& textureAsset) noexcept = default;

dooms::asset::TextureAsset::~TextureAsset()
{
	if(IsRenderingTextureProxyCreated())
	{
		DestroyRenderingTextureProxy();
	}
}

void dooms::asset::TextureAsset::OnSetPendingKill()
{
	Base::OnSetPendingKill();

	if (IsRenderingTextureProxyCreated())
	{
		DestroyRenderingTextureProxy();
	}
}

void dooms::asset::TextureAsset::OnEndImportInMainThread_Internal()
{
	D_START_PROFILING(Postprocess_Texture, eProfileLayers::Rendering);
	CreateRenderingTextureProxy();
	AllocateTextureResourceObject();
	D_END_PROFILING(Postprocess_Texture);
}

dooms::asset::eAssetType dooms::asset::TextureAsset::GetEAssetType() const
{
	return dooms::asset::eAssetType::TEXTURE;
}

dooms::graphics::GraphicsAPI::eTextureComponentFormat dooms::asset::TextureAsset::GetTextureComponentFormat() const
{
	return ComponentFormat;
}

dooms::graphics::GraphicsAPI::eTextureInternalFormat dooms::asset::TextureAsset::GetTextureInternalFormat() const
{
	return InternalFormat;
}

dooms::graphics::GraphicsAPI::eTextureCompressedInternalFormat dooms::asset::TextureAsset::GetTextureCompressedInternalFormat() const
{
	return CompressedInternalFormat;
}

UINT32 dooms::asset::TextureAsset::GetTextureWidth(const size_t mipLevelIndex) const
{
	D_ASSERT(mipLevelIndex < Width.size());
	return Width[mipLevelIndex];
}

UINT32 dooms::asset::TextureAsset::GetTextureHeight(const size_t mipLevelIndex) const
{
	D_ASSERT(mipLevelIndex < Height.size());
	return Height[mipLevelIndex];
}

UINT32 dooms::asset::TextureAsset::GetMipMapLevel() const
{
	return MipMapLevelCount;
}

UINT64 dooms::asset::TextureAsset::GetEntireImageSize() const
{
	return EntireImageSize;
}

dooms::graphics::GraphicsAPI::eDataType dooms::asset::TextureAsset::GetTextureDataType() const
{
	return dooms::graphics::GraphicsAPI::eDataType::UNSIGNED_BYTE;
}

dooms::graphics::RenderingTextureViewProxy* dooms::asset::TextureAsset::GenerateTextureView
(
	const UINT32 defaultBindingPosition,
	const graphics::GraphicsAPI::eGraphicsPipeLineStage defaultTargetGraphicsPipeLineStage
) const
{
	return dooms::CreateDObject<dooms::graphics::RenderingTextureViewProxy>(this, defaultBindingPosition, defaultTargetGraphicsPipeLineStage);
}

void dooms::asset::TextureAsset::CreateRenderingTextureProxy()
{
	D_ASSERT(TextureProxy == nullptr);

	TextureProxy = new dooms::graphics::RenderingTextureProxy();

	graphics::RenderingTextureProxy::FRenderingTextureProxyInitializer Initializer;
	Initializer.ScratchImage = std::move(ScratchImage);
	Initializer.TextureData = std::move(TextureData);
	Initializer.TargetTexture = TargetTexture;
	Initializer.TextureBindTarget = TextureBindTarget;
	Initializer.Width = Width;
	Initializer.Height = Height;
	Initializer.SrcRowPitch = SrcRowPitch;
	Initializer.SrcDepthPitch = SrcDepthPitch;
	Initializer.MipMapLevelCount = MipMapLevelCount;
	Initializer.ComponentFormat = ComponentFormat;
	Initializer.InternalFormat = InternalFormat;
	Initializer.CompressedInternalFormat = CompressedInternalFormat;
	Initializer.DataType = DataType;
	Initializer.BindFlags = BindFlags;

	TextureProxy->InitRenderingTextureProxy(Initializer);

	dooms::thread::RenderThread::GetSingleton()->EnqueueRenderCommand
	(
		[Proxy = TextureProxy]()
		{
			dooms::graphics::RenderingProxyManager::GetSingleton()->RenderingTextureProxyList.push_back(Proxy);
		}
	);
}

void dooms::asset::TextureAsset::CreateRenderingTextureProxyIfNotCreated()
{
	if(IsRenderingTextureProxyCreated() == false)
	{
		CreateRenderingTextureProxy();
	}
}

void dooms::asset::TextureAsset::DestroyRenderingTextureProxy()
{
	D_ASSERT(TextureProxy != nullptr);

	graphics::RenderingTextureProxy* const Proxy = TextureProxy;
	TextureProxy = nullptr;
	dooms::thread::RenderThread::GetSingleton()->EnqueueRenderCommand
	(
		[Proxy]()
		{
			dooms::graphics::RenderingProxyManager::GetSingleton()->DestroyedRenderingTextureProxyList.push_back(Proxy);
		}
	);
}

dooms::graphics::RenderingTextureProxy* dooms::asset::TextureAsset::GetRenderingTextureProxy() const
{
	return TextureProxy;
}

bool dooms::asset::TextureAsset::IsRenderingTextureProxyCreated() const
{
	return (TextureProxy != nullptr);
}

void dooms::asset::TextureAsset::AllocateTextureResourceObject()
{
	D_ASSERT(IsRenderingTextureProxyCreated());
	
	dooms::thread::RenderThread::GetSingleton()->EnqueueRenderCommand
	(
		[Proxy = TextureProxy]()
		{
			Proxy->AllocateTextureResourceObject();
		}
	);
}

void dooms::asset::TextureAsset::DestroyTextureResourceObject()
{
	D_ASSERT(IsRenderingTextureProxyCreated());

	dooms::thread::RenderThread::GetSingleton()->EnqueueRenderCommand
	(
		[Proxy = TextureProxy]()
		{
			Proxy->DestroyTextureResourceObject();
		}
	);
}

