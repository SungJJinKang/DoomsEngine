#include "Texture.h"

#include "../API/OpenglAPI.h"



using namespace doom::graphics;



Texture::Texture(eTextureType textureType, eBindTarget bindTarget,
	eTargetTexture targetTexture, eTextureInternalFormat internalFormat, eTextureCompressedInternalFormat compressedInternalFormat, unsigned int width, eTextureComponentFormat format, eDataType type)
	: mTextureType{ textureType }, mBindTarget{ bindTarget },
	mTarget{ targetTexture }, mInternalFormat{ internalFormat }, mCompressedInternalFormat{ compressedInternalFormat }, mWidth{ width }, mHeight{ 0 }, mDataFormat{ format }, mDataType{ type }
{
	D_ASSERT(mWidth > 0 && mHeight > 0);
	glGenTextures(1, &(mBufferID));
}


Texture::Texture(eTextureType textureType, eBindTarget bindTarget,
	eTargetTexture targetTexture, eTextureInternalFormat internalFormat, eTextureCompressedInternalFormat compressedInternalFormat, unsigned int width, unsigned int height, eTextureComponentFormat format, eDataType type)
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

Texture::~Texture()
{
	if (mBufferID.Get() != 0)
	{
		glDeleteTextures(1, &(mBufferID));
	}
	
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

doom::graphics::Texture::eWrapMode Texture::GetWrapModeS()
{
	return mWrapS;
}

doom::graphics::Texture::eWrapMode Texture::GetWrapModeT()
{
	return mWrapT;
}

doom::graphics::Texture::eWrapMode Texture::GetWrapModeR()
{
	return mWrapR;
}

unsigned int Texture::GetID()
{
	return mBufferID;
}



