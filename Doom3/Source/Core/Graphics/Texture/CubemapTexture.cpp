#include "CubemapTexture.h"

#include <glad/glad.h>

using namespace dooms::graphics;

CubemapTexture::CubemapTexture()
{
}

CubemapTexture::CubemapTexture(dooms::graphics::GraphicsAPI::eTextureType textureType, dooms::graphics::GraphicsAPI::eTargetTexture target, dooms::graphics::GraphicsAPI::eTextureInternalFormat internalFormat, UINT32 width, dooms::graphics::GraphicsAPI::eTextureComponentFormat format, dooms::graphics::GraphicsAPI::eDataType type, const void* data)
{
	InitializeCubemapTexture(textureType, target, internalFormat, width, format, type, data);
}

CubemapTexture::CubemapTexture(dooms::graphics::GraphicsAPI::eTextureType textureType, dooms::graphics::GraphicsAPI::eTargetTexture target, dooms::graphics::GraphicsAPI::eTextureInternalFormat internalFormat, UINT32 width, UINT32 height, dooms::graphics::GraphicsAPI::eTextureComponentFormat format, dooms::graphics::GraphicsAPI::eDataType type, const void* data)
{
	InitializeCubemapTexture(textureType, target, internalFormat, width, height, format, type, data);
}

CubemapTexture::CubemapTexture(dooms::graphics::GraphicsAPI::eTextureType textureType, dooms::graphics::GraphicsAPI::eTargetTexture target, dooms::graphics::GraphicsAPI::eTextureCompressedInternalFormat compressedInternalFormat, UINT32 width, dooms::graphics::GraphicsAPI::eTextureComponentFormat format, dooms::graphics::GraphicsAPI::eDataType type, const void* data)
{
	InitializeCubemapTexture(textureType, target, compressedInternalFormat, width, format, type, data);
}
CubemapTexture::CubemapTexture(dooms::graphics::GraphicsAPI::eTextureType textureType, dooms::graphics::GraphicsAPI::eTargetTexture target, dooms::graphics::GraphicsAPI::eTextureCompressedInternalFormat compressedInternalFormat, UINT32 width, UINT32 height, dooms::graphics::GraphicsAPI::eTextureComponentFormat format, dooms::graphics::GraphicsAPI::eDataType type, const void* data)
{
	InitializeCubemapTexture(textureType, target, compressedInternalFormat, width, height, format, type, data);
}

void CubemapTexture::TexImage1D(INT32 level, const void* data) const noexcept
{
	BindTexture();
	for (UINT32 i = 0; i < 6; i++)
	{
		GraphicsAPI::Define1DTextureStorageRequirement(mBindTarget, 0, mInternalFormat, mWidth);
		GraphicsAPI::UploadPixelsTo1DTexture(mBindTarget, 0, 0, mWidth, mDataFormat, mDataType, data);
		//glTexImage1D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, level, static_cast<UINT32>(mInternalFormat), mWidth, 0, static_cast<UINT32>(mDataFormat), static_cast<UINT32>(mDataType), data);
	}
}

void CubemapTexture::TexImage1D(INT32 face, INT32 level, const void* data) const noexcept
{
	BindTexture();
	GraphicsAPI::Define1DTextureStorageRequirement(mBindTarget, 0, mInternalFormat, mWidth);
	GraphicsAPI::UploadPixelsTo1DTexture(mBindTarget, 0, 0, mWidth, mDataFormat, mDataType, data);

	//glTexImage1D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, level, static_cast<UINT32>(mInternalFormat), mWidth, 0, static_cast<UINT32>(mDataFormat), static_cast<UINT32>(mDataType), data);
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

void CubemapTexture::InitializeCubemapTexture(dooms::graphics::GraphicsAPI::eTextureType textureType, dooms::graphics::GraphicsAPI::eTargetTexture target,
	dooms::graphics::GraphicsAPI::eTextureInternalFormat internalFormat, UINT32 width, dooms::graphics::GraphicsAPI::eTextureComponentFormat format, dooms::graphics::GraphicsAPI::eDataType type,
	const void* data)
{
	InitializeTexture(textureType, dooms::graphics::GraphicsAPI::eTextureBindTarget::TEXTURE_CUBE_MAP, target, internalFormat, dooms::graphics::GraphicsAPI::eTextureCompressedInternalFormat::TEXTURE_COMPRESSED_INTERNAL_FORMAT_NONE, width, format, type);
	TexImage1D(0, data);
}

void CubemapTexture::InitializeCubemapTexture(dooms::graphics::GraphicsAPI::eTextureType textureType, dooms::graphics::GraphicsAPI::eTargetTexture target,
	dooms::graphics::GraphicsAPI::eTextureInternalFormat internalFormat, UINT32 width, UINT32 height, dooms::graphics::GraphicsAPI::eTextureComponentFormat format, dooms::graphics::GraphicsAPI::eDataType type,
	const void* data)
{
	InitializeTexture(textureType, dooms::graphics::GraphicsAPI::eTextureBindTarget::TEXTURE_CUBE_MAP, target, internalFormat, dooms::graphics::GraphicsAPI::eTextureCompressedInternalFormat::TEXTURE_COMPRESSED_INTERNAL_FORMAT_NONE, width, height, format, type);
	TexImage2D(0, data);
}

void CubemapTexture::InitializeCubemapTexture(dooms::graphics::GraphicsAPI::eTextureType textureType, dooms::graphics::GraphicsAPI::eTargetTexture target,
	dooms::graphics::GraphicsAPI::eTextureCompressedInternalFormat compressedInternalFormat, UINT32 width, dooms::graphics::GraphicsAPI::eTextureComponentFormat format,
	dooms::graphics::GraphicsAPI::eDataType type, const void* data)
{
	InitializeTexture(textureType, dooms::graphics::GraphicsAPI::eTextureBindTarget::TEXTURE_CUBE_MAP, target, dooms::graphics::GraphicsAPI::eTextureInternalFormat::TEXTURE_INTERNAL_FORMAT_NONE, compressedInternalFormat, width, format, type);
	TexImage1D(0, data);
}

void CubemapTexture::InitializeCubemapTexture(dooms::graphics::GraphicsAPI::eTextureType textureType, dooms::graphics::GraphicsAPI::eTargetTexture target,
	dooms::graphics::GraphicsAPI::eTextureCompressedInternalFormat compressedInternalFormat, UINT32 width, UINT32 height,
	dooms::graphics::GraphicsAPI::eTextureComponentFormat format, dooms::graphics::GraphicsAPI::eDataType type, const void* data)
{
	InitializeTexture(textureType, dooms::graphics::GraphicsAPI::eTextureBindTarget::TEXTURE_CUBE_MAP, target, dooms::graphics::GraphicsAPI::eTextureInternalFormat::TEXTURE_INTERNAL_FORMAT_NONE, compressedInternalFormat, width, height, format, type);
	TexImage2D(0, data);
}
