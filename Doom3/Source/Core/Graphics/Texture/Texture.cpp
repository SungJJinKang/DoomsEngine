#include "Texture.h"

#include "../API/OpenglAPI.h"



using namespace doom::graphics;



Texture::Texture(eTextureType textureType, eBindTarget bindTarget,
	eTargetTexture targetTexture, eTextureInternalFormat internalFormat, eTextureCompressedInternalFormat compressedInternalFormat, UINT32 width, eTextureComponentFormat format, eDataType type)
	: mTextureType{ textureType }, mBindTarget{ bindTarget },
	mTarget{ targetTexture }, mInternalFormat{ internalFormat }, mCompressedInternalFormat{ compressedInternalFormat }, mWidth{ width }, mHeight{ 0 }, mDataFormat{ format }, mDataType{ type }
{
	D_ASSERT(mWidth > 0 && mHeight > 0);
	glGenTextures(1, &(mBufferID));
}


Texture::Texture(eTextureType textureType, eBindTarget bindTarget,
	eTargetTexture targetTexture, eTextureInternalFormat internalFormat, eTextureCompressedInternalFormat compressedInternalFormat, UINT32 width, UINT32 height, eTextureComponentFormat format, eDataType type)
	: mTextureType{ textureType }, mBindTarget{ bindTarget },
	mTarget{ targetTexture }, mInternalFormat{ internalFormat }, mCompressedInternalFormat{ compressedInternalFormat }, mWidth{ width }, mHeight{ height }, mDataFormat{ format }, mDataType{ type }
{
	D_ASSERT(mWidth > 0 && mHeight > 0);
	glGenTextures(1, &(mBufferID));
}


void Texture::OnEndContructor()
{
	SetFilterMin(Texture::eFilterMode::LINEAR, false);
	SetFilterMax(Texture::eFilterMode::LINEAR, false);
	SetWrapMode(Texture::eWrapMode::REPEAT, false);
	//UnBindTexture();
}

void Texture::DestroyTextureBufferObject()
{
	if (mBufferID.Get() != 0)
	{
		glDeleteTextures(1, &(mBufferID));
		mBufferID = 0;
	}
}

Texture::~Texture()
{
	DestroyTextureBufferObject();
}

void Texture::SetWrapMode(eWrapMode wrapMode, bool bBind)
{
	if (bBind)
	{
		BindTexture();
	}

	if (mTarget == eTargetTexture::TEXTURE_1D)
	{
		mWrapS = wrapMode;
		TexParameteri(mBindTarget, eTextureParameterType::TEXTURE_WRAP_S, static_cast<eTextureParameterValue>(wrapMode));
	}
	else if (mTarget == eTargetTexture::TEXTURE_2D)
	{
		mWrapS = wrapMode;
		mWrapT = wrapMode;
		TexParameteri(mBindTarget, eTextureParameterType::TEXTURE_WRAP_S, static_cast<eTextureParameterValue>(wrapMode));
		TexParameteri(mBindTarget, eTextureParameterType::TEXTURE_WRAP_T, static_cast<eTextureParameterValue>(wrapMode));
	}
	else if (mTarget == eTargetTexture::TEXTURE_3D)
	{
		mWrapS = wrapMode;
		mWrapT = wrapMode;
		mWrapR = wrapMode;
		TexParameteri(mBindTarget, eTextureParameterType::TEXTURE_WRAP_S, static_cast<eTextureParameterValue>(wrapMode));
		TexParameteri(mBindTarget, eTextureParameterType::TEXTURE_WRAP_T, static_cast<eTextureParameterValue>(wrapMode));
		TexParameteri(mBindTarget, eTextureParameterType::TEXTURE_WRAP_R, static_cast<eTextureParameterValue>(wrapMode));
	}
}

void Texture::SetFilterMin(eFilterMode filterMode, bool bBind)
{
	if (bBind)
	{
		BindTexture();
	}

	TexParameteri(mBindTarget, eTextureParameterType::TEXTURE_MIN_FILTER, static_cast<eTextureParameterValue>(filterMode));
}

void Texture::SetFilterMax(eFilterMode filterMode, bool bBind)
{
	if (bBind)
	{
		BindTexture();
	}

	TexParameteri(mBindTarget, eTextureParameterType::TEXTURE_MAG_FILTER, static_cast<eTextureParameterValue>(filterMode));
}

doom::graphics::Texture::eWrapMode Texture::GetWrapModeS() const
{
	return mWrapS;
}

doom::graphics::Texture::eWrapMode Texture::GetWrapModeT() const
{
	return mWrapT;
}

doom::graphics::Texture::eWrapMode Texture::GetWrapModeR() const
{
	return mWrapR;
}

FLOAT32 Texture::GetTextureMetaDataFLOAT32(const INT32 lodLevel, const eTextureMataDataType textureMetaDataType) const
{
	float data;

	BindTexture();
	glGetTexLevelParameterfv(static_cast<UINT32>(mBindTarget), lodLevel, static_cast<UINT32>(textureMetaDataType), &data);

	return data;
}

INT32 Texture::GetTextureMetaDataINT32(const INT32 lodLevel, const eTextureMataDataType textureMetaDataType) const
{
	INT32 data;

	BindTexture();
	glGetTexLevelParameteriv(static_cast<UINT32>(mBindTarget), lodLevel, static_cast<UINT32>(textureMetaDataType), &data);

	return data;
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
	
	UINT8* pixels = new UINT8[bufferSize];

	glGetTexImage(static_cast<UINT32>(mBindTarget), lodLevel, static_cast<UINT32>(mDataFormat), static_cast<UINT32>(mDataType), reinterpret_cast<void*>(pixels));

	return pixels;
}

INT32 Texture::GetTextureBufferSize(const INT32 lodLevel) const
{
	const INT32 width = GetTextureMetaDataINT32(lodLevel, eTextureMataDataType::TEXTURE_WIDTH);
	const INT32 height = GetTextureMetaDataINT32(lodLevel, eTextureMataDataType::TEXTURE_HEIGHT);

	return GetTextureBufferSizeStatic(width, height, mDataFormat, mDataType);
}


INT32 Texture::GetTextureBufferSizeStatic
(
	const INT32 width, 
	const INT32 height,
	const eTextureComponentFormat dataFormat,
	const eDataType dataType
	
)
{
	int PixelDataSize = 1;
	switch (dataType)
	{
	case eDataType::UNSIGNED_BYTE:

		PixelDataSize = 1;
		break;

	case eDataType::FLOAT:

		PixelDataSize = 4;
		break;

	case eDataType::UNSIGNED_INT_24_8:

		PixelDataSize = 4;
		break;
		
	default:

		NEVER_HAPPEN;
	}
	
	INT32 bufferSize = PixelDataSize * width * height;
	
	switch (dataFormat)
	{

	case eTextureComponentFormat::RED:
	case eTextureComponentFormat::RED_INTEGER:
		bufferSize *= 1;
		break;

	case eTextureComponentFormat::RG:
	case eTextureComponentFormat::RG_INTEGER:
		bufferSize *= 2;
		break;

	case eTextureComponentFormat::RGB:
	case eTextureComponentFormat::RGB_INTEGER:
	case eTextureComponentFormat::BGR_INTEGER:
	case eTextureComponentFormat::BGR:
		bufferSize *= 3;
		break;

	case eTextureComponentFormat::RGBA:
	case eTextureComponentFormat::RGBA_INTEGER:
	case eTextureComponentFormat::BGRA:
	case eTextureComponentFormat::BGRA_INTEGER:
		bufferSize *= 4;
		break;

	case eTextureComponentFormat::DEPTH_COMPONENT:
		//bufferSize *= bufferSize;
		break;

	case eTextureComponentFormat::DEPTH_STENCIL:
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



