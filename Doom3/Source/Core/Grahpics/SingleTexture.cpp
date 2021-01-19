#include "SingleTexture.h"

Doom::SingleTexture::SingleTexture(TextureType textureType, TargetTexture target, InternalFormat internalFormat, unsigned int width, unsigned int height, DataFormat format, DataType type, const void* data)
	: Texture{textureType, BindTarget::TEXTURE_2D, target, internalFormat, width, height, format, type, data}
{
	this->TexImage2D(0, _InternalFormat, Width, Height, _DataFormat, _DataType, data);
}

void Doom::SingleTexture::TexImage2D(int level, InternalFormat internalformat, int width, int height, DataFormat format, DataType type, const void* data)
{
	this->BindTexture();

	glTexImage2D(GL_TEXTURE_2D, level, static_cast<unsigned int>(internalformat), width, height, 0, static_cast<unsigned int>(format), static_cast<unsigned int>(type), data);
}