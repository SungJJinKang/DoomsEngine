#include "CubemapTexture.h"

using namespace doom::graphics;

CubemapTexture::CubemapTexture(eTextureType textureType, eTargetTexture target, eTextureInternalFormat internalFormat, unsigned int width, eTextureComponentFormat format, eDataType type, const void* data)
	: Texture{ textureType, eBindTarget::TEXTURE_CUBE_MAP, target, internalFormat, eTextureCompressedInternalFormat::NONE, width, format, type }
{
	TexImage1D(0, data);
}

CubemapTexture::CubemapTexture(eTextureType textureType, eTargetTexture target, eTextureInternalFormat internalFormat, unsigned int width, unsigned int height, eTextureComponentFormat format, eDataType type, const void* data)
	: Texture{ textureType, eBindTarget::TEXTURE_CUBE_MAP, target, internalFormat, eTextureCompressedInternalFormat::NONE, width, height, format, type }
{
	TexImage2D(0, data);
}

CubemapTexture::CubemapTexture(eTextureType textureType, eTargetTexture target, eTextureCompressedInternalFormat compressedInternalFormat, unsigned int width, eTextureComponentFormat format, eDataType type, const void* data)
	: Texture{ textureType, eBindTarget::TEXTURE_CUBE_MAP, target, eTextureInternalFormat::NONE, compressedInternalFormat, width, format, type }
{
	TexImage1D(0, data);
}
CubemapTexture::CubemapTexture(eTextureType textureType, eTargetTexture target, eTextureCompressedInternalFormat compressedInternalFormat, unsigned int width, unsigned int height, eTextureComponentFormat format, eDataType type, const void* data)
	: Texture{ textureType, eBindTarget::TEXTURE_CUBE_MAP, target, eTextureInternalFormat::NONE, compressedInternalFormat, width, height, format, type }
{
	TexImage2D(0, data);
}

void CubemapTexture::TexImage1D(int level, const void* data) const noexcept
{
	BindTexture();
	for (unsigned int i = 0; i < 6; i++)
	{
		glTexImage1D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, level, static_cast<unsigned int>(mInternalFormat), mWidth, 0, static_cast<unsigned int>(mDataFormat), static_cast<unsigned int>(mDataType), data);
	}
}

void CubemapTexture::TexImage1D(int face, int level, const void* data) const noexcept
{
	BindTexture();
	glTexImage1D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, level, static_cast<unsigned int>(mInternalFormat), mWidth, 0, static_cast<unsigned int>(mDataFormat), static_cast<unsigned int>(mDataType), data);
}

void CubemapTexture::TexImage2D(int level, const void* data) const noexcept
{
	BindTexture();
	for (unsigned int i = 0; i < 6; i++)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, level, static_cast<unsigned int>(mInternalFormat), mWidth, mHeight, 0, static_cast<unsigned int>(mDataFormat), static_cast<unsigned int>(mDataType), data);
	}
}

void CubemapTexture::TexImage2D(int face, int level, const void* data) const noexcept
{
	BindTexture();
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, level, static_cast<unsigned int>(mInternalFormat), mWidth, mHeight, 0, static_cast<unsigned int>(mDataFormat), static_cast<unsigned int>(mDataType), data);
}
