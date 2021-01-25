#include "Texture.h"

#include "../API/OpenglAPI.h"



using namespace doom::graphics;


Texture::Texture(eTextureType textureType, eBindTarget bindTarget,
	eTargetTexture targetTexture, eInternalFormat internalFormat, unsigned int width, unsigned int height, eDataFormat format, eDataType type, const void* data = nullptr)
	: mTextureType{ textureType }, mBindTarget{ bindTarget },
	mTarget{ targetTexture }, mInternalFormat{ internalFormat }, mWidth{ width }, mHeight{ height }, mDataFormat{ format }, mDataType{ type }
{
	//TODO : use glGenTexture(texturecount ~ , ) for multiple textures at once
	glGenTextures(1, &(this->mID));
	this->BindTexture();
	//this->TexImage2D(0, _InternalFormat, Width, Height, _DataFormat, _DataType, data);
}

Texture::~Texture()
{
	glDeleteTextures(1, &(this->mID));
}


void Texture::BindTexture()
{
	ONLY_DEBUG
	(
	if (mCurrentBoundId[this->mBindTarget] == this->mID)
	{
		DEBUG_LOG("This Texture is already bound");
		return;
	}
	)

	glBindTexture(static_cast<unsigned int>(this->mBindTarget), this->mID);
	ONLY_DEBUG(mCurrentBoundId[this->mBindTarget] = this->mID;)
	
}

void Texture::UnBindTexture()
{
	glBindTexture(static_cast<unsigned int>(this->mBindTarget), 0);
	ONLY_DEBUG(mCurrentBoundId[this->mBindTarget] = 0;)
}

void Texture::ActiveTexture(unsigned int index)
{
	glActiveTexture(GL_TEXTURE0 + index);
}

void Texture::TexParameterf(eBindTarget target, eTextureParameterType pname, eTextureParameterValue param)
{
	glTexParameterf(static_cast<unsigned int>(target), static_cast<unsigned int>(pname), static_cast<float>(param));
}

void Texture::TexParameteri(eBindTarget target, eTextureParameterType pname, float param)
{
	glTexParameterf(static_cast<unsigned int>(target), static_cast<unsigned int>(pname), param);
}

void Texture::TexParameteri(eBindTarget target, eTextureParameterType pname, eTextureParameterValue param)
{
	glTexParameteri(static_cast<unsigned int>(target), static_cast<unsigned int>(pname), static_cast<unsigned int>(param));
}

void Texture::TexParameterf(eBindTarget target, eTextureParameterType pname, unsigned int param)
{
	glTexParameteri(static_cast<unsigned int>(target), static_cast<unsigned int>(pname), param);
}



