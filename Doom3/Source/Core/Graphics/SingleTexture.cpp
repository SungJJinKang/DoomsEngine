#include "SingleTexture.h"

#include <DirectXTex.h>

using namespace doom::graphics;


SingleTexture::SingleTexture(eTextureType textureType, eTargetTexture target, eTextureInternalFormat internalFormat, unsigned int width, eTextureComponentFormat format, eDataType type, const void* data)
	: Texture{ textureType, eBindTarget::TEXTURE_2D, target, internalFormat, eTextureCompressedInternalFormat::NONE, width, format, type }
{
	this->TexImage1D(0, data);

	this->OnEndContructor();
}

SingleTexture::SingleTexture(eTextureType textureType, eTargetTexture target, eTextureInternalFormat internalFormat, unsigned int width, unsigned int height, eTextureComponentFormat format, eDataType type, const void* data)
	: Texture{textureType, eBindTarget::TEXTURE_2D, target, internalFormat, eTextureCompressedInternalFormat::NONE, width, height, format, type }
{
	this->TexImage2D(0, data);

	this->OnEndContructor();
}

SingleTexture::SingleTexture(eTextureType textureType, eTargetTexture target, eTextureCompressedInternalFormat compressedInternalFormat, unsigned int width, eTextureComponentFormat format, eDataType type, const void* data)
	: Texture{ textureType, eBindTarget::TEXTURE_2D, target, eTextureInternalFormat::NONE, compressedInternalFormat, width, format, type }
{
	this->TexImage2D(0, data);

	this->OnEndContructor();
}

SingleTexture::SingleTexture(eTextureType textureType, eTargetTexture target, eTextureCompressedInternalFormat compressedInternalFormat, unsigned int width, unsigned int height, eTextureComponentFormat format, eDataType type, const void* data)
	: Texture{ textureType, eBindTarget::TEXTURE_2D, target, eTextureInternalFormat::NONE, compressedInternalFormat, width, height, format, type }
{
	this->TexImage2D(0, data);

	this->OnEndContructor();
}

void doom::graphics::SingleTexture::TexMipMapImages(std::vector<const DirectX::Image*> mipmapDatas)
{
	this->BindTexture();
	for (unsigned int i = 0; i < mipmapDatas.size(); i++)
	{
		this->TexImage2D(i, mipmapDatas[i]);
	}
}

void SingleTexture::TexImage1D(int level, const DirectX::Image* directXImage) noexcept
{
	if (this->mInternalFormat != eTextureInternalFormat::NONE)
	{
		glTexImage1D(GL_TEXTURE_1D, level, static_cast<unsigned int>(this->mInternalFormat), directXImage->width,  0, static_cast<unsigned int>(this->mDataFormat), static_cast<unsigned int>(this->mDataType), directXImage->pixels);
	}
	else if (this->mCompressedInternalFormat != eTextureCompressedInternalFormat::NONE)
	{
		glCompressedTexImage1D(GL_TEXTURE_2D, level, static_cast<unsigned int>(this->mCompressedInternalFormat), directXImage->width, 0, directXImage->slicePitch, directXImage->pixels);
	}
	else
	{
		NODEFAULT;
	}
}

void SingleTexture::TexImage2D(int level, const DirectX::Image* directXImage) noexcept
{
	if (this->mInternalFormat != eTextureInternalFormat::NONE)
	{
		glTexImage2D(GL_TEXTURE_1D, level, static_cast<unsigned int>(this->mInternalFormat), directXImage->width, directXImage->height, 0, static_cast<unsigned int>(this->mDataFormat), static_cast<unsigned int>(this->mDataType), directXImage->pixels);
	}
	else if (this->mCompressedInternalFormat != eTextureCompressedInternalFormat::NONE)
	{
// 		img.rowPitch = /*<number of bytes in a scanline of the source data>*/;
// 		img.slicePitch = /*<number of bytes in the entire 2D image>*/;
		glCompressedTexImage2D(GL_TEXTURE_2D, level, static_cast<unsigned int>(this->mCompressedInternalFormat), directXImage->width, directXImage->height, 0, directXImage->slicePitch, directXImage->pixels);
	}
	else
	{
		NODEFAULT;
	}
}

SingleTexture::SingleTexture(eTextureType textureType, eTargetTexture target, eTextureInternalFormat internalFormat, unsigned int width, eTextureComponentFormat format, eDataType type, std::vector<const DirectX::Image*> mipmapDatas)
	: Texture{ textureType, eBindTarget::TEXTURE_2D, target, internalFormat,  eTextureCompressedInternalFormat::NONE, width, format, type }
{
	TexMipMapImages(mipmapDatas);

	this->OnEndContructor();
}

SingleTexture::SingleTexture(eTextureType textureType, eTargetTexture target, eTextureInternalFormat internalFormat, unsigned int width, unsigned int height, eTextureComponentFormat format, eDataType type, std::vector<const DirectX::Image*> mipmapDatas)
	: Texture{ textureType, eBindTarget::TEXTURE_2D, target, internalFormat, eTextureCompressedInternalFormat::NONE, width, height, format, type }
{
	TexMipMapImages(mipmapDatas);

	this->OnEndContructor();
}

SingleTexture::SingleTexture(eTextureType textureType, eTargetTexture target, eTextureCompressedInternalFormat compressedInternalFormat, unsigned int width, eTextureComponentFormat format, eDataType type, std::vector<const DirectX::Image*> mipmapDatas)
	: Texture{ textureType, eBindTarget::TEXTURE_2D, target, eTextureInternalFormat::NONE, compressedInternalFormat, width, format, type }
{
	TexMipMapImages(mipmapDatas);

	this->OnEndContructor();
}

SingleTexture::SingleTexture(eTextureType textureType, eTargetTexture target, eTextureCompressedInternalFormat compressedInternalFormat, unsigned int width, unsigned int height, eTextureComponentFormat format, eDataType type, std::vector<const DirectX::Image*> mipmapDatas)
	: Texture{ textureType, eBindTarget::TEXTURE_2D, target, eTextureInternalFormat::NONE, compressedInternalFormat, width, height, format, type }
{
	TexMipMapImages(mipmapDatas);

	this->OnEndContructor();
}
