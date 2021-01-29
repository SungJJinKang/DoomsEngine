#include "CubemapTexture.h"

using namespace doom::graphics;

CubemapTexture::CubemapTexture(eTextureType textureType, eTargetTexture target, eInternalFormat internalFormat, unsigned int width, eDataFormat format, eDataType type, const void* data)
	: Texture{ textureType, eBindTarget::TEXTURE_CUBE_MAP, target, internalFormat, width, format, type, data }
{
	this->TexImage1D(0, mInternalFormat, mWidth, mDataFormat, mDataType, data);
}

CubemapTexture::CubemapTexture(eTextureType textureType, eTargetTexture target, eInternalFormat internalFormat, unsigned int width, unsigned int height, eDataFormat format, eDataType type, const void* data)
	: Texture{ textureType, eBindTarget::TEXTURE_CUBE_MAP, target, internalFormat, width, height, format, type, data }
{
	this->TexImage2D(0, mInternalFormat, mWidth, mHeight, mDataFormat, mDataType, data);
}



void CubemapTexture::TexImage1D(int level, eInternalFormat internalformat, int width, eDataFormat format, eDataType type, const void* data)
{
	this->BindTexture();

	for (unsigned int i = 0; i < 6; i++)
	{
		glTexImage1D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, level, static_cast<unsigned int>(internalformat), width, 0, static_cast<unsigned int>(format), static_cast<unsigned int>(type), data);
	}
}

void CubemapTexture::TexImage1D(int face, int level, eInternalFormat internalformat, int width, eDataFormat format, eDataType type, const void* data)
{
	this->BindTexture();
	glTexImage1D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, level, static_cast<unsigned int>(internalformat), width, 0, static_cast<unsigned int>(format), static_cast<unsigned int>(type), data);
}


void CubemapTexture::TexImage2D(int level, eInternalFormat internalformat, int width, int height, eDataFormat format, eDataType type, const void* data)
{
	this->BindTexture();

	for (unsigned int i = 0; i < 6; i++)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, level, static_cast<unsigned int>(internalformat), width, height, 0, static_cast<unsigned int>(format), static_cast<unsigned int>(type), data);
	}
}


void CubemapTexture::TexImage2D(int face, int level, eInternalFormat internalformat, int width, int height, eDataFormat format, eDataType type, const void* data)
{
	this->BindTexture();
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, level, static_cast<unsigned int>(internalformat), width, height, 0, static_cast<unsigned int>(format), static_cast<unsigned int>(type), data);
}

