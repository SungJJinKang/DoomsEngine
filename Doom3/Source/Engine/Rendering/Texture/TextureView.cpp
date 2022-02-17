#include "TextureView.h"


UINT64 dooms::graphics::TextureView::BOUND_TEXTURE_ID[GRAPHICS_PIPELINE_STAGE_COUNT][MAX_TEXTURE_BOUND_LOCATION_COUNT]{};

void dooms::graphics::TextureView::OnEndContructor()
{

	/*
	SetFilterMin(GraphicsAPI::eFilterMode::FILTER_MODE_LINEAR, false);
	SetFilterMax(GraphicsAPI::eFilterMode::FILTER_MODE_LINEAR, false);
	SetWrapMode(GraphicsAPI::eWrapMode::WRAP_MODE_REPEAT, false);
	*/

}

const dooms::asset::TextureAsset* dooms::graphics::TextureView::GetTargetTextureResourceObject() const
{
	return mTargetTextureResourceObject;
}

void dooms::graphics::TextureView::SetDefaultBindingLocation(const UINT32 defaultBindingLocation)
{
	mDefaultBindingLocation = defaultBindingLocation;
}

void dooms::graphics::TextureView::SetDefaultTargetGraphicsPipeLineStage(const GraphicsAPI::eGraphicsPipeLineStage defaultGraphicsPipeLineStage)
{
	mDefaultTargetGraphicsPipeLineStage = defaultGraphicsPipeLineStage;
}

dooms::graphics::TextureView::~TextureView()
{
	DestroyTextureViewObject();
}


void dooms::graphics::TextureView::OnSetPendingKill()
{
	DObject::OnSetPendingKill();

	DestroyTextureViewObject();
	
}

void dooms::graphics::TextureView::DestroyTextureViewObject()
{
	if(mTextureViewObject.IsValid())
	{
		GraphicsAPI::DestroyTextureViewObject(mTextureViewObject);
		mTextureViewObject.Reset();
	}
}

dooms::graphics::TextureView::TextureView
(
	const asset::TextureAsset* const textureResourceObject,
	const UINT32 defaultBindingPosition,
	const GraphicsAPI::eGraphicsPipeLineStage defaultTargetGraphicsPipeLineStage
)
	: mTextureViewObject(), mTargetTextureResourceObject(textureResourceObject), mDefaultBindingLocation(defaultBindingPosition), mDefaultTargetGraphicsPipeLineStage(defaultTargetGraphicsPipeLineStage)
{
	mTextureViewObject = GraphicsAPI::CreateTextureViewObject(textureResourceObject->GetTextureResourceObject());
}

dooms::graphics::TextureView::TextureView(const TextureView& textureView)
	:
	mTargetTextureResourceObject(textureView.mTargetTextureResourceObject),
	mTextureViewObject( (IsValid(textureView.mTargetTextureResourceObject) == true) ? GraphicsAPI::CreateTextureViewObject(textureView.mTargetTextureResourceObject->GetTextureResourceObject()) : BufferID::INVALID_BUFFER_ID),
	mDefaultBindingLocation(textureView.mDefaultBindingLocation),
	mDefaultTargetGraphicsPipeLineStage(textureView.mDefaultTargetGraphicsPipeLineStage)
{
	
}

dooms::graphics::TextureView& dooms::graphics::TextureView::operator=(const TextureView& textureView)
{
	DestroyTextureViewObject();

	mTargetTextureResourceObject = textureView.mTargetTextureResourceObject;
	mTextureViewObject = (IsValid(mTargetTextureResourceObject) == true) ? GraphicsAPI::CreateTextureViewObject(textureView.mTargetTextureResourceObject->GetTextureResourceObject()) : BufferID::INVALID_BUFFER_ID;
	mDefaultBindingLocation = textureView.mDefaultBindingLocation;
	mDefaultTargetGraphicsPipeLineStage = textureView.mDefaultTargetGraphicsPipeLineStage;

	return *this;
}

dooms::graphics::TextureView::TextureView(TextureView&& textureView) noexcept
{
	mTargetTextureResourceObject = textureView.mTargetTextureResourceObject;
	textureView.mTargetTextureResourceObject = nullptr;

	mTextureViewObject = textureView.mTextureViewObject;
	textureView.mTextureViewObject.Reset();

	mDefaultBindingLocation = textureView.mDefaultBindingLocation;
	mDefaultTargetGraphicsPipeLineStage = textureView.mDefaultTargetGraphicsPipeLineStage;
}

dooms::graphics::TextureView& dooms::graphics::TextureView::operator=(TextureView&& textureView) noexcept
{
	DestroyTextureViewObject();

	mTargetTextureResourceObject = textureView.mTargetTextureResourceObject;
	textureView.mTargetTextureResourceObject = nullptr;

	mTextureViewObject = textureView.mTextureViewObject;
	textureView.mTextureViewObject.Reset();

	mDefaultBindingLocation = textureView.mDefaultBindingLocation;
	mDefaultTargetGraphicsPipeLineStage = textureView.mDefaultTargetGraphicsPipeLineStage;

	return *this;
}

FLOAT32 dooms::graphics::TextureView::GetTextureMetaDataFLOAT32(const INT32 lodLevel, const GraphicsAPI::eTextureMetaDataType textureMetaDataType) const
{
	return 	GraphicsAPI::GetTextureMetaDataFloat(mTextureViewObject, graphics::GraphicsAPI::eTextureBindTarget::TEXTURE_2D, lodLevel, textureMetaDataType);
}

INT32 dooms::graphics::TextureView::GetTextureMetaDataINT32(const INT32 lodLevel, const GraphicsAPI::eTextureMetaDataType textureMetaDataType) const
{
	return GraphicsAPI::GetTextureMetaDataInt(mTextureViewObject, graphics::GraphicsAPI::eTextureBindTarget::TEXTURE_2D, lodLevel, textureMetaDataType);
}


//TODO : https://stackoverflow.com/a/62965713 Implement GetTexturePixel using memory mapped io, Make MapBuffer Class for managing it

const std::unique_ptr<UINT8[]> dooms::graphics::TextureView::GetTexturePixels(const INT32 lodLevel) const
{
	return std::unique_ptr<UINT8[]>(const_cast<UINT8*>(GetTexturePixelsUnsafe(lodLevel)));
}

UINT8* dooms::graphics::TextureView::GetTexturePixelsUnsafe(const INT32 lodLevel ) const
{
	//BindTexture();
	
	INT32 bufferSize = GetTextureBufferSize(lodLevel);
	D_ASSERT(bufferSize != 0);
	
	return GraphicsAPI::FetchTexturePixels(graphics::GraphicsAPI::eTextureBindTarget::TEXTURE_2D, lodLevel, mTargetTextureResourceObject->GetTextureComponentFormat(), mTargetTextureResourceObject->GetTextureDataType(), bufferSize);
}

INT32 dooms::graphics::TextureView::GetTextureBufferSize(const INT32 lodLevel) const
{
	const INT32 width = GetTextureMetaDataINT32(lodLevel, GraphicsAPI::eTextureMetaDataType::TEXTURE_WIDTH);
	const INT32 height = GetTextureMetaDataINT32(lodLevel, GraphicsAPI::eTextureMetaDataType::TEXTURE_HEIGHT);

	return GetTextureBufferSizeStatic(width, height, mTargetTextureResourceObject->GetTextureComponentFormat(), mTargetTextureResourceObject->GetTextureDataType());
}


INT32 dooms::graphics::TextureView::GetTextureBufferSizeStatic
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


const dooms::graphics::BufferID& dooms::graphics::TextureView::GetTextureBufferID() const
{
	D_ASSERT(mTextureViewObject.IsValid());
	return mTextureViewObject;
}



