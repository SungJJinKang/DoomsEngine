#include "TextureView.h"




using namespace dooms::graphics;



void TextureView::OnEndContructor()
{

	/*
	SetFilterMin(GraphicsAPI::eFilterMode::FILTER_MODE_LINEAR, false);
	SetFilterMax(GraphicsAPI::eFilterMode::FILTER_MODE_LINEAR, false);
	SetWrapMode(GraphicsAPI::eWrapMode::WRAP_MODE_REPEAT, false);
	*/

}

dooms::asset::TextureAsset* TextureView::GetTargetTextureResourceObject()
{
	return mTargetTextureResourceObject;
}

const dooms::asset::TextureAsset* TextureView::GetTargetTextureResourceObject() const
{
	return mTargetTextureResourceObject;
}

TextureView::~TextureView()
{
	DestroyTextureViewObject();
}


void TextureView::OnSetPendingKill()
{
	DObject::OnSetPendingKill();

	DestroyTextureViewObject();
	
}

void TextureView::DestroyTextureViewObject()
{
	if(mTextureViewObject.IsValid())
	{
		GraphicsAPI::DestroyTextureViewObject(mTextureViewObject);
	}
}

TextureView::TextureView(asset::TextureAsset* const textureResourceObject, const UINT32 bindingLocation)
	: mTargetTextureResourceObject(textureResourceObject), mBindingLocation(bindingLocation)
{
	mTextureViewObject = GraphicsAPI::CreateTextureViewObject(textureResourceObject->GetTextureResourceObject());
}

FLOAT32 TextureView::GetTextureMetaDataFLOAT32(const INT32 lodLevel, const GraphicsAPI::eTextureMetaDataType textureMetaDataType) const
{
	return 	GraphicsAPI::GetTextureMetaDataFloat(mTextureViewObject, graphics::GraphicsAPI::eTextureBindTarget::TEXTURE_2D, lodLevel, textureMetaDataType);
}

INT32 TextureView::GetTextureMetaDataINT32(const INT32 lodLevel, const GraphicsAPI::eTextureMetaDataType textureMetaDataType) const
{
	return GraphicsAPI::GetTextureMetaDataInt(mTextureViewObject, graphics::GraphicsAPI::eTextureBindTarget::TEXTURE_2D, lodLevel, textureMetaDataType);
}


//TODO : https://stackoverflow.com/a/62965713 Implement GetTexturePixel using memory mapped io, Make MapBuffer Class for managing it

const std::unique_ptr<UINT8[]> TextureView::GetTexturePixels(const INT32 lodLevel) const
{
	return std::unique_ptr<UINT8[]>(const_cast<UINT8*>(GetTexturePixelsUnsafe(lodLevel)));
}

UINT8* TextureView::GetTexturePixelsUnsafe(const INT32 lodLevel ) const
{
	BindTexture();
	
	INT32 bufferSize = GetTextureBufferSize(lodLevel);
	D_ASSERT(bufferSize != 0);
	
	return GraphicsAPI::FetchTexturePixels(graphics::GraphicsAPI::eTextureBindTarget::TEXTURE_2D, lodLevel, mTargetTextureResourceObject->GetTextureComponentFormat(), mTargetTextureResourceObject->GetTextureDataType(), bufferSize);
}

INT32 TextureView::GetTextureBufferSize(const INT32 lodLevel) const
{
	const INT32 width = GetTextureMetaDataINT32(lodLevel, GraphicsAPI::eTextureMetaDataType::TEXTURE_WIDTH);
	const INT32 height = GetTextureMetaDataINT32(lodLevel, GraphicsAPI::eTextureMetaDataType::TEXTURE_HEIGHT);

	return GetTextureBufferSizeStatic(width, height, mTargetTextureResourceObject->GetTextureComponentFormat(), mTargetTextureResourceObject->GetTextureDataType());
}


INT32 TextureView::GetTextureBufferSizeStatic
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


const BufferID& TextureView::GetTextureBufferID() const
{
	D_ASSERT(mTextureViewObject.IsValid());
	return mTextureViewObject;
}


