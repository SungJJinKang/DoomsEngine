#include "SingleTexture.h"

using namespace doom::graphics;

SingleTexture::SingleTexture(eTextureType textureType, eTargetTexture target, eInternalFormat internalFormat, unsigned int width, unsigned int height, eDataFormat format, eDataType type, const void* data)
	: Texture{textureType, eBindTarget::TEXTURE_2D, target, internalFormat, width, height, format, type, data}
{
	this->TexImage2D(0, mInternalFormat, mWidth, mHeight, mDataFormat, mDataType, data);
}

void SingleTexture::TexImage2D(int level, eInternalFormat internalformat, int width, int height, eDataFormat format, eDataType type, const void* data)
{
	this->BindTexture();

	glTexImage2D(GL_TEXTURE_2D, level, static_cast<unsigned int>(internalformat), width, height, 0, static_cast<unsigned int>(format), static_cast<unsigned int>(type), data);
}