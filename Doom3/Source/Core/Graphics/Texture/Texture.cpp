#include "Texture.h"




using namespace dooms::graphics;

Texture::Texture()
	: mBufferID()
{
}

Texture::~Texture()
{
	DestroyTextureBufferObject();
}


Texture::Texture(GraphicsAPI::eTextureType textureType, GraphicsAPI::eTextureBindTarget bindTarget,
	GraphicsAPI::eTargetTexture targetTexture, GraphicsAPI::eTextureInternalFormat internalFormat, GraphicsAPI::eTextureCompressedInternalFormat compressedInternalFormat, UINT32 width, GraphicsAPI::eTextureComponentFormat format, GraphicsAPI::eDataType type)
	: mBufferID()
{
	InitializeTexture(textureType, bindTarget, targetTexture, internalFormat, compressedInternalFormat, width, format, type);
}


Texture::Texture(GraphicsAPI::eTextureType textureType, GraphicsAPI::eTextureBindTarget bindTarget,
	GraphicsAPI::eTargetTexture targetTexture, GraphicsAPI::eTextureInternalFormat internalFormat, GraphicsAPI::eTextureCompressedInternalFormat compressedInternalFormat, UINT32 width, UINT32 height, GraphicsAPI::eTextureComponentFormat format, GraphicsAPI::eDataType type)
	: mBufferID()
{
	InitializeTexture(textureType, bindTarget, targetTexture, internalFormat, compressedInternalFormat, width, height, format, type);
}


void Texture::OnEndContructor()
{
	SetFilterMin(GraphicsAPI::eFilterMode::FILTER_MODE_LINEAR, false);
	SetFilterMax(GraphicsAPI::eFilterMode::FILTER_MODE_LINEAR, false);
	SetWrapMode(GraphicsAPI::eWrapMode::WRAP_MODE_REPEAT, false);
	//UnBindTexture();
}

void Texture::InitializeTexture(GraphicsAPI::eTextureType textureType, GraphicsAPI::eTextureBindTarget bindTarget, GraphicsAPI::eTargetTexture targetTexture,
	GraphicsAPI::eTextureInternalFormat internalFormat, GraphicsAPI::eTextureCompressedInternalFormat compressedInternalFormat, UINT32 width,
	GraphicsAPI::eTextureComponentFormat format, GraphicsAPI::eDataType type)
{
	D_ASSERT(mBufferID.IsValid() == false);
	D_ASSERT(mWidth > 0 && mHeight > 0);
	if(mBufferID.IsValid() == false)
	{
		mTextureType = textureType;
		mBindTarget = bindTarget;
		mTarget = targetTexture;
		mInternalFormat = internalFormat;
		mCompressedInternalFormat = compressedInternalFormat;
		mWidth = width;
		mHeight = 0;
		mDataFormat = format;
		mDataType = type;

		mBufferID = GraphicsAPI::CreateTextureObject();
	}
}

void Texture::InitializeTexture(GraphicsAPI::eTextureType textureType, GraphicsAPI::eTextureBindTarget bindTarget, GraphicsAPI::eTargetTexture targetTexture,
	GraphicsAPI::eTextureInternalFormat internalFormat, GraphicsAPI::eTextureCompressedInternalFormat compressedInternalFormat, UINT32 width,
	UINT32 height, GraphicsAPI::eTextureComponentFormat format, GraphicsAPI::eDataType type)
{
	if (mBufferID.IsValid() == false)
	{
		mTextureType = textureType;
		mBindTarget = bindTarget;
		mTarget = targetTexture;
		mInternalFormat = internalFormat;
		mCompressedInternalFormat = compressedInternalFormat;
		mWidth = width;
		mHeight = height;
		mDataFormat = format;
		mDataType = type;

		mBufferID = GraphicsAPI::CreateTextureObject();
	}
}

void Texture::DestroyTextureBufferObject()
{
	if (mBufferID.GetBufferID() != 0)
	{
		GraphicsAPI::DestroyTextureObject(mBufferID);
		mBufferID = 0;
	}
}


void Texture::SetWrapMode(GraphicsAPI::eWrapMode wrapMode, bool bBind)
{
	if (bBind)
	{
		BindTexture();
	}

	if (mTarget == GraphicsAPI::eTargetTexture::TARGET_TEXTURE_TEXTURE_1D)
	{
		mWrapS = wrapMode;
		GraphicsAPI::SetTextureWrapMode_S(mBindTarget, wrapMode);
	}
	else if (mTarget == GraphicsAPI::eTargetTexture::TARGET_TEXTURE_TEXTURE_2D)
	{
		mWrapS = wrapMode;
		mWrapT = wrapMode;
		GraphicsAPI::SetTextureWrapMode_S(mBindTarget, wrapMode);
		GraphicsAPI::SetTextureWrapMode_T(mBindTarget, wrapMode);
	}
	else if (mTarget == GraphicsAPI::eTargetTexture::TARGET_TEXTURE_TEXTURE_3D)
	{
		mWrapS = wrapMode;
		mWrapT = wrapMode;
		mWrapR = wrapMode;
		GraphicsAPI::SetTextureWrapMode_S(mBindTarget, wrapMode);
		GraphicsAPI::SetTextureWrapMode_T(mBindTarget, wrapMode);
		GraphicsAPI::SetTextureWrapMode_R(mBindTarget, wrapMode);
	}
}

void Texture::SetFilterMin(GraphicsAPI::eFilterMode filterMode, bool bBind)
{
	if (bBind)
	{
		BindTexture();
	}

	GraphicsAPI::SetMinFilter(mBindTarget, filterMode);
}

void Texture::SetFilterMax(GraphicsAPI::eFilterMode filterMode, bool bBind)
{
	if (bBind)
	{
		BindTexture();
	}

	GraphicsAPI::SetMagFilter(mBindTarget, filterMode);
}

dooms::graphics::GraphicsAPI::eWrapMode Texture::GetWrapModeS() const
{
	return mWrapS;
}

dooms::graphics::GraphicsAPI::eWrapMode Texture::GetWrapModeT() const
{
	return mWrapT;
}

dooms::graphics::GraphicsAPI::eWrapMode Texture::GetWrapModeR() const
{
	return mWrapR;
}

FLOAT32 Texture::GetTextureMetaDataFLOAT32(const INT32 lodLevel, const GraphicsAPI::eTextureMetaDataType textureMetaDataType) const
{
	return 	GraphicsAPI::GetTextureMetaDataFloat(mBufferID, mBindTarget, lodLevel, textureMetaDataType);
}

INT32 Texture::GetTextureMetaDataINT32(const INT32 lodLevel, const GraphicsAPI::eTextureMetaDataType textureMetaDataType) const
{
	return GraphicsAPI::GetTextureMetaDataInt(mBufferID, mBindTarget, lodLevel, textureMetaDataType);
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
	
	return GraphicsAPI::FetchTexturePixels(mBindTarget, lodLevel, mDataFormat, mDataType, bufferSize);
}

INT32 Texture::GetTextureBufferSize(const INT32 lodLevel) const
{
	const INT32 width = GetTextureMetaDataINT32(lodLevel, GraphicsAPI::eTextureMetaDataType::TEXTURE_WIDTH);
	const INT32 height = GetTextureMetaDataINT32(lodLevel, GraphicsAPI::eTextureMetaDataType::TEXTURE_HEIGHT);

	return GetTextureBufferSizeStatic(width, height, mDataFormat, mDataType);
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


UINT32 Texture::GetTextureBufferID() const
{
	D_ASSERT(mBufferID != 0);
	return mBufferID;
}



