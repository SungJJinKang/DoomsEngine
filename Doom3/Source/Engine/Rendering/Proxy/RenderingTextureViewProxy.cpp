#include "RenderingTextureViewProxy.h"

#include <Rendering/Proxy/RenderingTextureProxy.h>

UINT64 dooms::graphics::RenderingTextureViewProxy::BOUND_TEXTURE_ID[GRAPHICS_PIPELINE_STAGE_COUNT][MAX_TEXTURE_BOUND_LOCATION_COUNT]{};

void dooms::graphics::RenderingTextureViewProxy::OnEndContructor()
{

	/*
	SetFilterMin(GraphicsAPI::eFilterMode::FILTER_MODE_LINEAR, false);
	SetFilterMax(GraphicsAPI::eFilterMode::FILTER_MODE_LINEAR, false);
	SetWrapMode(GraphicsAPI::eWrapMode::WRAP_MODE_REPEAT, false);
	*/

}

const dooms::graphics::RenderingTextureProxy* dooms::graphics::RenderingTextureViewProxy::GetTargetTextureResourceObject() const
{
	return TargetTextureProxy;
}

void dooms::graphics::RenderingTextureViewProxy::SetDefaultBindingLocation(const UINT32 defaultBindingLocation)
{
	DefaultBindingLocation = defaultBindingLocation;
}

void dooms::graphics::RenderingTextureViewProxy::SetDefaultTargetGraphicsPipeLineStage(const GraphicsAPI::eGraphicsPipeLineStage defaultGraphicsPipeLineStage)
{
	DefaultTargetGraphicsPipeLineStage = defaultGraphicsPipeLineStage;
}

void dooms::graphics::RenderingTextureViewProxy::BindTexture() const noexcept
{
	if (BOUND_TEXTURE_ID[static_cast<UINT32>(DefaultTargetGraphicsPipeLineStage)][DefaultBindingLocation] != TextureViewObject.GetBufferID())
	{
		BOUND_TEXTURE_ID[static_cast<UINT32>(DefaultTargetGraphicsPipeLineStage)][DefaultBindingLocation] = TextureViewObject.GetBufferID();
		GraphicsAPI::BindTextureObject
		(
			TextureViewObject,
			TargetTextureProxy->GetTextureBindTarget(),
			DefaultBindingLocation,
			DefaultTargetGraphicsPipeLineStage
		);
	}
}

void dooms::graphics::RenderingTextureViewProxy::BindTexture(const UINT32 bindingPoint, const GraphicsAPI::eGraphicsPipeLineStage targetPipeLineStage) const noexcept
{
	if (BOUND_TEXTURE_ID[static_cast<UINT32>(targetPipeLineStage)][bindingPoint] != TextureViewObject.GetBufferID())
	{
		BOUND_TEXTURE_ID[static_cast<UINT32>(targetPipeLineStage)][bindingPoint] = TextureViewObject;

		GraphicsAPI::BindTextureObject
		(
			TextureViewObject,
			TargetTextureProxy->GetTextureBindTarget(),
			bindingPoint,
			targetPipeLineStage
		);
	}
}

void dooms::graphics::RenderingTextureViewProxy::UnBindTexture() const noexcept
{
	if (BOUND_TEXTURE_ID[static_cast<UINT32>(DefaultTargetGraphicsPipeLineStage)][DefaultBindingLocation] != 0)
	{
		BOUND_TEXTURE_ID[static_cast<UINT32>(DefaultTargetGraphicsPipeLineStage)][DefaultBindingLocation] = 0;

		GraphicsAPI::BindTextureObject
		(
			0,
			TargetTextureProxy->GetTextureBindTarget(),
			DefaultBindingLocation,
			DefaultTargetGraphicsPipeLineStage
		);
	}
}

void dooms::graphics::RenderingTextureViewProxy::UnBindTexture(const UINT32 bindingPoint, const GraphicsAPI::eGraphicsPipeLineStage targetPipeLineStage) const noexcept
{
	if (BOUND_TEXTURE_ID[static_cast<UINT32>(targetPipeLineStage)][bindingPoint] != 0)
	{
		BOUND_TEXTURE_ID[static_cast<UINT32>(targetPipeLineStage)][bindingPoint] = 0;

		GraphicsAPI::BindTextureObject
		(
			0,
			TargetTextureProxy->GetTextureBindTarget(),
			bindingPoint,
			targetPipeLineStage
		);
	}
}

dooms::graphics::RenderingTextureViewProxy::~RenderingTextureViewProxy()
{
	DestroyTextureViewObjectIfExist();
}

void dooms::graphics::RenderingTextureViewProxy::DestroyTextureViewObjectIfExist()
{
	if(TextureViewObject.IsValid())
	{
		GraphicsAPI::DestroyTextureViewObject(TextureViewObject);
		TextureViewObject.Reset();
	}
}

dooms::graphics::RenderingTextureViewProxy::RenderingTextureViewProxy
(
	const RenderingTextureProxy* const TextureProxy,
	const UINT32 DefaultBindingPosition,
	const GraphicsAPI::eGraphicsPipeLineStage DefaultTargetGraphicsPipeLineStage
)
	: TextureViewObject(), TargetTextureProxy(TextureProxy), DefaultBindingLocation(DefaultBindingPosition), DefaultTargetGraphicsPipeLineStage(DefaultTargetGraphicsPipeLineStage)
{
	TextureViewObject = GraphicsAPI::CreateTextureViewObject(TextureProxy->GetTextureResourceObject());
}

dooms::graphics::RenderingTextureViewProxy::RenderingTextureViewProxy(const RenderingTextureViewProxy& TextureViewProxy)
	:
	TargetTextureProxy(TextureViewProxy.TargetTextureProxy),
	TextureViewObject( (TextureViewProxy.TargetTextureProxy != nullptr) ? GraphicsAPI::CreateTextureViewObject(TextureViewProxy.TargetTextureProxy->GetTextureResourceObject()) : BufferID::INVALID_BUFFER_ID),
	DefaultBindingLocation(TextureViewProxy.DefaultBindingLocation),
	DefaultTargetGraphicsPipeLineStage(TextureViewProxy.DefaultTargetGraphicsPipeLineStage)
{
	
}

dooms::graphics::RenderingTextureViewProxy& dooms::graphics::RenderingTextureViewProxy::operator=(const RenderingTextureViewProxy& textureView)
{
	DestroyTextureViewObjectIfExist();

	TargetTextureProxy = textureView.TargetTextureProxy;
	TextureViewObject = (textureView.TargetTextureProxy != nullptr) ? GraphicsAPI::CreateTextureViewObject(textureView.TargetTextureProxy->GetTextureResourceObject()) : BufferID::INVALID_BUFFER_ID;
	DefaultBindingLocation = textureView.DefaultBindingLocation;
	DefaultTargetGraphicsPipeLineStage = textureView.DefaultTargetGraphicsPipeLineStage;

	return *this;
}

dooms::graphics::RenderingTextureViewProxy::RenderingTextureViewProxy(RenderingTextureViewProxy&& textureView) noexcept
{
	TargetTextureProxy = textureView.TargetTextureProxy;
	textureView.TargetTextureProxy = nullptr;

	TextureViewObject = textureView.TextureViewObject;
	textureView.TextureViewObject.Reset();

	DefaultBindingLocation = textureView.DefaultBindingLocation;
	DefaultTargetGraphicsPipeLineStage = textureView.DefaultTargetGraphicsPipeLineStage;
}

dooms::graphics::RenderingTextureViewProxy& dooms::graphics::RenderingTextureViewProxy::operator=(RenderingTextureViewProxy&& textureView) noexcept
{
	DestroyTextureViewObjectIfExist();

	TargetTextureProxy = textureView.TargetTextureProxy;
	textureView.TargetTextureProxy = nullptr;

	TextureViewObject = textureView.TextureViewObject;
	textureView.TextureViewObject.Reset();

	DefaultBindingLocation = textureView.DefaultBindingLocation;
	DefaultTargetGraphicsPipeLineStage = textureView.DefaultTargetGraphicsPipeLineStage;

	return *this;
}

FLOAT32 dooms::graphics::RenderingTextureViewProxy::GetTextureMetaDataFLOAT32(const INT32 lodLevel, const GraphicsAPI::eTextureMetaDataType textureMetaDataType) const
{
	return 	GraphicsAPI::GetTextureMetaDataFloat(TextureViewObject, graphics::GraphicsAPI::eTextureBindTarget::TEXTURE_2D, lodLevel, textureMetaDataType);
}

INT32 dooms::graphics::RenderingTextureViewProxy::GetTextureMetaDataINT32(const INT32 lodLevel, const GraphicsAPI::eTextureMetaDataType textureMetaDataType) const
{
	return GraphicsAPI::GetTextureMetaDataInt(TextureViewObject, graphics::GraphicsAPI::eTextureBindTarget::TEXTURE_2D, lodLevel, textureMetaDataType);
}


//TODO : https://stackoverflow.com/a/62965713 Implement GetTexturePixel using memory mapped io, Make MapBuffer Class for managing it

const std::unique_ptr<UINT8[]> dooms::graphics::RenderingTextureViewProxy::GetTexturePixels(const INT32 lodLevel) const
{
	return std::unique_ptr<UINT8[]>(const_cast<UINT8*>(GetTexturePixelsUnsafe(lodLevel)));
}

UINT8* dooms::graphics::RenderingTextureViewProxy::GetTexturePixelsUnsafe(const INT32 lodLevel ) const
{
	//BindTexture();
	
	INT32 bufferSize = GetTextureBufferSize(lodLevel);
	D_ASSERT(bufferSize != 0);
	
	return GraphicsAPI::FetchTexturePixels(graphics::GraphicsAPI::eTextureBindTarget::TEXTURE_2D, lodLevel, TargetTextureProxy->GetTextureComponentFormat(), TargetTextureProxy->GetTextureDataType(), bufferSize);
}

INT32 dooms::graphics::RenderingTextureViewProxy::GetTextureBufferSize(const INT32 lodLevel) const
{
	const INT32 width = GetTextureMetaDataINT32(lodLevel, GraphicsAPI::eTextureMetaDataType::TEXTURE_WIDTH);
	const INT32 height = GetTextureMetaDataINT32(lodLevel, GraphicsAPI::eTextureMetaDataType::TEXTURE_HEIGHT);

	return GetTextureBufferSizeStatic(width, height, TargetTextureProxy->GetTextureComponentFormat(), TargetTextureProxy->GetTextureDataType());
}


INT32 dooms::graphics::RenderingTextureViewProxy::GetTextureBufferSizeStatic
(
	const INT32 width, 
	const INT32 height,
	const GraphicsAPI::eTextureComponentFormat dataFormat,
	const GraphicsAPI::eDataType dataType
	
)
{
	int PixelDataSize = 1;
	switch (dataType)
	{
	case GraphicsAPI::eDataType::UNSIGNED_BYTE:

		PixelDataSize = 1;
		break;

	case GraphicsAPI::eDataType::FLOAT:

		PixelDataSize = 4;
		break;

	case GraphicsAPI::eDataType::UNSIGNED_INT_24_8:

		PixelDataSize = 4;
		break;
		
	default:

		NEVER_HAPPEN;
	}
	
	INT32 bufferSize = PixelDataSize * width * height;
	
	switch (dataFormat)
	{

	case GraphicsAPI::eTextureComponentFormat::TEXTURE_COMPONENT_RED:
	case GraphicsAPI::eTextureComponentFormat::TEXTURE_COMPONENT_RED_INTEGER:
		bufferSize *= 1;
		break;

	case GraphicsAPI::eTextureComponentFormat::TEXTURE_COMPONENT_RG:
	case GraphicsAPI::eTextureComponentFormat::TEXTURE_COMPONENT_RG_INTEGER:
		bufferSize *= 2;
		break;

	case GraphicsAPI::eTextureComponentFormat::TEXTURE_COMPONENT_RGB:
	case GraphicsAPI::eTextureComponentFormat::TEXTURE_COMPONENT_RGB_INTEGER:
	case GraphicsAPI::eTextureComponentFormat::TEXTURE_COMPONENT_BGR_INTEGER:
	case GraphicsAPI::eTextureComponentFormat::TEXTURE_COMPONENT_BGR:
		bufferSize *= 3;
		break;

	case GraphicsAPI::eTextureComponentFormat::TEXTURE_COMPONENT_RGBA:
	case GraphicsAPI::eTextureComponentFormat::TEXTURE_COMPONENT_RGBA_INTEGER:
	case GraphicsAPI::eTextureComponentFormat::TEXTURE_COMPONENT_BGRA:
	case GraphicsAPI::eTextureComponentFormat::TEXTURE_COMPONENT_BGRA_INTEGER:
		bufferSize *= 4;
		break;

	case GraphicsAPI::eTextureComponentFormat::TEXTURE_COMPONENT_DEPTH_COMPONENT:
		//bufferSize *= bufferSize;
		break;

	case GraphicsAPI::eTextureComponentFormat::TEXTURE_COMPONENT_DEPTH_STENCIL:
		//bufferSize *= 2;
		break;

	default:
		NEVER_HAPPEN;
	}

	return bufferSize;
}


const dooms::graphics::BufferID& dooms::graphics::RenderingTextureViewProxy::GetTextureBufferID() const
{
	D_ASSERT(TextureViewObject.IsValid());
	return TextureViewObject;
}



