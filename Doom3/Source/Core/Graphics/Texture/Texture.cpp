#include "Texture.h"




using namespace dooms::graphics;



void Texture::OnEndContructor()
{
	SetFilterMin(GraphicsAPI::eFilterMode::FILTER_MODE_LINEAR, false);
	SetFilterMax(GraphicsAPI::eFilterMode::FILTER_MODE_LINEAR, false);
	SetWrapMode(GraphicsAPI::eWrapMode::WRAP_MODE_REPEAT, false);
	//UnBindTexture();
}

dooms::asset::TextureAsset* Texture::GetTargetTextureResourceObject()
{
	return mTargetTextureResourceObject;
}

const dooms::asset::TextureAsset* Texture::GetTargetTextureResourceObject() const
{
	return mTargetTextureResourceObject;
}

Texture::~Texture()
{
	DestroyTextureViewObject();
}


void Texture::OnSetPendingKill()
{
	DObject::OnSetPendingKill();

	DestroyTextureViewObject();
	
}

void Texture::DestroyTextureViewObject()
{
	if(mTextureViewObject.IsValid())
	{
		GraphicsAPI::DestroyTextureViewObject(mTextureViewObject);
	}
}

Texture::Texture(asset::TextureAsset* const textureResourceObject)
	: mTargetTextureResourceObject{textureResourceObject}
{
	mTextureViewObject = GraphicsAPI::CreateTextureViewObject(textureResourceObject->GetTextureResourceObject());
}

FLOAT32 Texture::GetTextureMetaDataFLOAT32(const INT32 lodLevel, const GraphicsAPI::eTextureMetaDataType textureMetaDataType) const
{
	return 	GraphicsAPI::GetTextureMetaDataFloat(mTextureViewObject, graphics::GraphicsAPI::eTextureBindTarget::TEXTURE_2D, lodLevel, textureMetaDataType);
}

INT32 Texture::GetTextureMetaDataINT32(const INT32 lodLevel, const GraphicsAPI::eTextureMetaDataType textureMetaDataType) const
{
	return GraphicsAPI::GetTextureMetaDataInt(mTextureViewObject, graphics::GraphicsAPI::eTextureBindTarget::TEXTURE_2D, lodLevel, textureMetaDataType);
}


//TODO : https://stackoverflow.com/a/62965713 Implement GetTexturePixel using memory mapped io, Make MapBuffer Class for managing it

const std::unique_ptr<UINT8[]> Texture::GetTexturePixels(const INT32 lodLevel) const
{
	return std::unique_ptr<UINT8[]>(const_cast<UINT8*>(GetTexturePixelsUnsafe(lodLevel)));
}

UINT8* Texture::GetTexturePixelsUnsafe(const INT32 lodLevel ) const
{
	BindTexture();
	
	INT32 bufferSize = GetTextureBufferSize(lodLevel);
	D_ASSERT(bufferSize != 0);
	
	return GraphicsAPI::FetchTexturePixels(graphics::GraphicsAPI::eTextureBindTarget::TEXTURE_2D, lodLevel, mTargetTextureResourceObject->GetTextureComponentFormat(), mTargetTextureResourceObject->GetTextureDataType(), bufferSize);
}

INT32 Texture::GetTextureBufferSize(const INT32 lodLevel) const
{
	const INT32 width = GetTextureMetaDataINT32(lodLevel, GraphicsAPI::eTextureMetaDataType::TEXTURE_WIDTH);
	const INT32 height = GetTextureMetaDataINT32(lodLevel, GraphicsAPI::eTextureMetaDataType::TEXTURE_HEIGHT);

	return GetTextureBufferSizeStatic(width, height, mTargetTextureResourceObject->GetTextureComponentFormat(), mTargetTextureResourceObject->GetTextureDataType());
}


INT32 Texture::GetTextureBufferSizeStatic
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


const BufferID& Texture::GetTextureBufferID() const
{
	D_ASSERT(mBufferID.IsValid());
	return mTextureViewObject;
}



