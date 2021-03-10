#include "CubemapTexture.h"

using namespace doom::graphics;

CubemapTexture::CubemapTexture(eTextureType textureType, eTargetTexture target, eTextureInternalFormat internalFormat, unsigned int width, eTextureComponentFormat format, eDataType type, const void* data)
	: Texture{ textureType, eBindTarget::TEXTURE_CUBE_MAP, target, internalFormat, eTextureCompressedInternalFormat::NONE, width, format, type }
{
	this->TexImage1D(0, data);
}

CubemapTexture::CubemapTexture(eTextureType textureType, eTargetTexture target, eTextureInternalFormat internalFormat, unsigned int width, unsigned int height, eTextureComponentFormat format, eDataType type, const void* data)
	: Texture{ textureType, eBindTarget::TEXTURE_CUBE_MAP, target, internalFormat, eTextureCompressedInternalFormat::NONE, width, height, format, type }
{
	this->TexImage2D(0, data);
}

CubemapTexture::CubemapTexture(eTextureType textureType, eTargetTexture target, eTextureCompressedInternalFormat compressedInternalFormat, unsigned int width, eTextureComponentFormat format, eDataType type, const void* data)
	: Texture{ textureType, eBindTarget::TEXTURE_CUBE_MAP, target, eTextureInternalFormat::NONE, compressedInternalFormat, width, format, type }
{
	this->TexImage1D(0, data);
}
CubemapTexture::CubemapTexture(eTextureType textureType, eTargetTexture target, eTextureCompressedInternalFormat compressedInternalFormat, unsigned int width, unsigned int height, eTextureComponentFormat format, eDataType type, const void* data)
	: Texture{ textureType, eBindTarget::TEXTURE_CUBE_MAP, target, eTextureInternalFormat::NONE, compressedInternalFormat, width, height, format, type }
{
	this->TexImage2D(0, data);
}