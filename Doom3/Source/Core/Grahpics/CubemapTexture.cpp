#include "CubemapTexture.h"

Doom::CubemapTexture::CubemapTexture(TextureType textureType, TargetTexture target, InternalFormat internalFormat, unsigned int width, unsigned int height, DataFormat format, DataType type, const void* data)
	: Texture{ textureType, BindTarget::TEXTURE_CUBE_MAP, target, internalFormat, width, height, format, type, data }
{
	this->TexImage2D(0, _InternalFormat, Width, Height, _DataFormat, _DataType, data);
}

void Doom::CubemapTexture::TexImage2D(int level, InternalFormat internalformat, int width, int height, DataFormat format, DataType type, const void* data)
{
	this->BindTexture();

	for (unsigned int i = 0; i < 6; i++)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, level, static_cast<unsigned int>(internalformat), width, height, 0, static_cast<unsigned int>(format), static_cast<unsigned int>(type), data);
	}
}


void Doom::CubemapTexture::TexImage2D(int face, int level, InternalFormat internalformat, int width, int height, DataFormat format, DataType type, const void* data)
{
	this->BindTexture();
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, level, static_cast<unsigned int>(internalformat), width, height, 0, static_cast<unsigned int>(format), static_cast<unsigned int>(type), data);
}
