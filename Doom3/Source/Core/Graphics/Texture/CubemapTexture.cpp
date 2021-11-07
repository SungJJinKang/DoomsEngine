#include "CubemapTexture.h"

using namespace dooms::graphics;

CubemapTexture::CubemapTexture()
{
}

CubemapTexture::CubemapTexture(eTextureType textureType, eTargetTexture target, eTextureInternalFormat internalFormat, UINT32 width, eTextureComponentFormat format, eDataType type, const void* data)
{
	InitializeCubemapTexture(textureType, target, internalFormat, width, format, type, data);
}

CubemapTexture::CubemapTexture(eTextureType textureType, eTargetTexture target, eTextureInternalFormat internalFormat, UINT32 width, UINT32 height, eTextureComponentFormat format, eDataType type, const void* data)
{
	InitializeCubemapTexture(textureType, target, internalFormat, width, height, format, type, data);
}

CubemapTexture::CubemapTexture(eTextureType textureType, eTargetTexture target, eTextureCompressedInternalFormat compressedInternalFormat, UINT32 width, eTextureComponentFormat format, eDataType type, const void* data)
{
	InitializeCubemapTexture(textureType, target, compressedInternalFormat, width, format, type, data);
}
CubemapTexture::CubemapTexture(eTextureType textureType, eTargetTexture target, eTextureCompressedInternalFormat compressedInternalFormat, UINT32 width, UINT32 height, eTextureComponentFormat format, eDataType type, const void* data)
{
	InitializeCubemapTexture(textureType, target, compressedInternalFormat, width, height, format, type, data);
}

void CubemapTexture::TexImage1D(INT32 level, const void* data) const noexcept
{
	BindTexture();
	for (UINT32 i = 0; i < 6; i++)
	{
		glTexImage1D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, level, static_cast<UINT32>(mInternalFormat), mWidth, 0, static_cast<UINT32>(mDataFormat), static_cast<UINT32>(mDataType), data);
	}
}

void CubemapTexture::TexImage1D(INT32 face, INT32 level, const void* data) const noexcept
{
	BindTexture();
	glTexImage1D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, level, static_cast<UINT32>(mInternalFormat), mWidth, 0, static_cast<UINT32>(mDataFormat), static_cast<UINT32>(mDataType), data);
}

void CubemapTexture::TexImage2D(INT32 level, const void* data) const noexcept
{
	BindTexture();
	for (UINT32 i = 0; i < 6; i++)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, level, static_cast<UINT32>(mInternalFormat), mWidth, mHeight, 0, static_cast<UINT32>(mDataFormat), static_cast<UINT32>(mDataType), data);
	}
}

void CubemapTexture::TexImage2D(INT32 face, INT32 level, const void* data) const noexcept
{
	BindTexture();
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, level, static_cast<UINT32>(mInternalFormat), mWidth, mHeight, 0, static_cast<UINT32>(mDataFormat), static_cast<UINT32>(mDataType), data);
}

void CubemapTexture::InitializeCubemapTexture(eTextureType textureType, eTargetTexture target,
	eTextureInternalFormat internalFormat, UINT32 width, eTextureComponentFormat format, eDataType type,
	const void* data)
{
	InitializeTexture(textureType, eBindTarget::TEXTURE_CUBE_MAP, target, internalFormat, eTextureCompressedInternalFormat::NONE, width, format, type);
	TexImage1D(0, data);
}

void CubemapTexture::InitializeCubemapTexture(eTextureType textureType, eTargetTexture target,
	eTextureInternalFormat internalFormat, UINT32 width, UINT32 height, eTextureComponentFormat format, eDataType type,
	const void* data)
{
	InitializeTexture(textureType, eBindTarget::TEXTURE_CUBE_MAP, target, internalFormat, eTextureCompressedInternalFormat::NONE, width, height, format, type);
	TexImage2D(0, data);
}

void CubemapTexture::InitializeCubemapTexture(eTextureType textureType, eTargetTexture target,
	eTextureCompressedInternalFormat compressedInternalFormat, UINT32 width, eTextureComponentFormat format,
	eDataType type, const void* data)
{
	InitializeTexture(textureType, eBindTarget::TEXTURE_CUBE_MAP, target, eTextureInternalFormat::NONE, compressedInternalFormat, width, format, type);
	TexImage1D(0, data);
}

void CubemapTexture::InitializeCubemapTexture(eTextureType textureType, eTargetTexture target,
	eTextureCompressedInternalFormat compressedInternalFormat, UINT32 width, UINT32 height,
	eTextureComponentFormat format, eDataType type, const void* data)
{
	InitializeTexture(textureType, eBindTarget::TEXTURE_CUBE_MAP, target, eTextureInternalFormat::NONE, compressedInternalFormat, width, height, format, type);
	TexImage2D(0, data);
}
