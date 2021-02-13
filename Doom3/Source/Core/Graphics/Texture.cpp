#include "Texture.h"

#include "../API/OpenglAPI.h"



using namespace doom::graphics;


Texture::Texture(eTextureType textureType, eBindTarget bindTarget,
	eTargetTexture targetTexture, eInternalFormat internalFormat, unsigned int width, eDataFormat format, eDataType type, const void* data = nullptr)
	: mTextureType{ textureType }, mBindTarget{ bindTarget },
	mTarget{ targetTexture }, mInternalFormat{ internalFormat }, mWidth{ width }, mHeight{ 0 }, mDataFormat{ format }, mDataType{ type }
{
	D_ASSERT(mWidth > 0 && mHeight > 0);
	glGenTextures(1, &(this->mID));
}


Texture::Texture(eTextureType textureType, eBindTarget bindTarget,
	eTargetTexture targetTexture, eInternalFormat internalFormat, unsigned int width, unsigned int height, eDataFormat format, eDataType type, const void* data = nullptr)
	: mTextureType{ textureType }, mBindTarget{ bindTarget },
	mTarget{ targetTexture }, mInternalFormat{ internalFormat }, mWidth{ width }, mHeight{ height }, mDataFormat{ format }, mDataType{ type }
{
	D_ASSERT(mWidth > 0 && mHeight > 0);
	glGenTextures(1, &(this->mID));
}


void Texture::OnEndContructor()
{
	this->SetFilterMin(Texture::eFilterMode::LINEAR, false);
	this->SetFilterMax(Texture::eFilterMode::LINEAR, false);
	this->SetWrapMode(Texture::eWrapMode::REPEAT, false);
	//this->UnBindTexture();
}

Texture::~Texture()
{
	glDeleteTextures(1, &(this->mID));
}

void Texture::SetWrapMode(eWrapMode wrapMode, bool bBind)
{
	if (bBind)
	{
		this->BindTexture();
	}

	if (this->mTarget == eTargetTexture::TEXTURE_1D)
	{
		this->mWrapS = wrapMode;
		TexParameteri(this->mBindTarget, eTextureParameterType::TEXTURE_WRAP_S, static_cast<eTextureParameterValue>(wrapMode));
	}
	else if (this->mTarget == eTargetTexture::TEXTURE_2D)
	{
		this->mWrapS = wrapMode;
		this->mWrapT = wrapMode;
		TexParameteri(this->mBindTarget, eTextureParameterType::TEXTURE_WRAP_S, static_cast<eTextureParameterValue>(wrapMode));
		TexParameteri(this->mBindTarget, eTextureParameterType::TEXTURE_WRAP_T, static_cast<eTextureParameterValue>(wrapMode));
	}
	else if (this->mTarget == eTargetTexture::TEXTURE_3D)
	{
		this->mWrapS = wrapMode;
		this->mWrapT = wrapMode;
		this->mWrapR = wrapMode;
		TexParameteri(this->mBindTarget, eTextureParameterType::TEXTURE_WRAP_S, static_cast<eTextureParameterValue>(wrapMode));
		TexParameteri(this->mBindTarget, eTextureParameterType::TEXTURE_WRAP_T, static_cast<eTextureParameterValue>(wrapMode));
		TexParameteri(this->mBindTarget, eTextureParameterType::TEXTURE_WRAP_R, static_cast<eTextureParameterValue>(wrapMode));
	}
}

void Texture::SetFilterMin(eFilterMode filterMode, bool bBind)
{
	if (bBind)
	{
		this->BindTexture();
	}

	TexParameteri(this->mBindTarget, eTextureParameterType::TEXTURE_MIN_FILTER, static_cast<eTextureParameterValue>(filterMode));
}

void Texture::SetFilterMax(eFilterMode filterMode, bool bBind)
{
	if (bBind)
	{
		this->BindTexture();
	}

	TexParameteri(this->mBindTarget, eTextureParameterType::TEXTURE_MAG_FILTER, static_cast<eTextureParameterValue>(filterMode));
}

doom::graphics::Texture::eWrapMode Texture::GetWrapModeS()
{
	return this->mWrapS;
}

doom::graphics::Texture::eWrapMode Texture::GetWrapModeT()
{
	return this->mWrapT;
}

doom::graphics::Texture::eWrapMode Texture::GetWrapModeR()
{
	return this->mWrapR;
}
