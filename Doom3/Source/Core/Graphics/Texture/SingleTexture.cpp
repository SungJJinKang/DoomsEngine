#include "SingleTexture.h"

#include <DirectXTex.h>

using namespace doom::graphics;


SingleTexture::SingleTexture(eTextureType textureType, eTargetTexture target, eTextureInternalFormat internalFormat, unsigned int width, eTextureComponentFormat format, eDataType type, const void* data)
	: Texture{ textureType, eBindTarget::TEXTURE_2D, target, internalFormat, eTextureCompressedInternalFormat::NONE, width, format, type }
{
	TexImage1D(0, data);

	OnEndContructor();
}

SingleTexture::SingleTexture(eTextureType textureType, eTargetTexture target, eTextureInternalFormat internalFormat, unsigned int width, unsigned int height, eTextureComponentFormat format, eDataType type, const void* data)
	: Texture{textureType, eBindTarget::TEXTURE_2D, target, internalFormat, eTextureCompressedInternalFormat::NONE, width, height, format, type }
{
	TexImage2D(0, data);

	OnEndContructor();
}

SingleTexture::SingleTexture(eTextureType textureType, eTargetTexture target, eTextureCompressedInternalFormat compressedInternalFormat, unsigned int width, eTextureComponentFormat format, eDataType type, const void* data)
	: Texture{ textureType, eBindTarget::TEXTURE_2D, target, eTextureInternalFormat::NONE, compressedInternalFormat, width, format, type }
{
	TexImage2D(0, data);

	OnEndContructor();
}

SingleTexture::SingleTexture(eTextureType textureType, eTargetTexture target, eTextureCompressedInternalFormat compressedInternalFormat, unsigned int width, unsigned int height, eTextureComponentFormat format, eDataType type, const void* data)
	: Texture{ textureType, eBindTarget::TEXTURE_2D, target, eTextureInternalFormat::NONE, compressedInternalFormat, width, height, format, type }
{
	TexImage2D(0, data);

	OnEndContructor();
}

void doom::graphics::SingleTexture::Tex2DMipMapImages(std::vector<const DirectX::Image*> mipmapDatas)
{
	BindTexture();

	if (mInternalFormat != eTextureInternalFormat::NONE)
	{
		for (unsigned int i = 0; i < mipmapDatas.size(); i++)
		{
			glTexImage2D(GL_TEXTURE_2D, i, static_cast<unsigned int>(mInternalFormat), static_cast<int>(mipmapDatas[i]->width), static_cast<int>(mipmapDatas[i]->height), 0, static_cast<unsigned int>(mDataFormat), static_cast<unsigned int>(mDataType), mipmapDatas[i]->pixels);
		}

	}
	else if (mCompressedInternalFormat != eTextureCompressedInternalFormat::NONE)
	{
		for (unsigned int i = 0; i < mipmapDatas.size(); i++)
		{
			glCompressedTexImage2D(GL_TEXTURE_2D, i, static_cast<unsigned int>(mCompressedInternalFormat), static_cast<int>(mipmapDatas[i]->width), static_cast<int>(mipmapDatas[i]->height), 0, static_cast<int>(mipmapDatas[i]->slicePitch), mipmapDatas[i]->pixels);
		}

	}
	else
	{
		NEVER_HAPPEN;
	}

	
	TexParameteri(Texture::eBindTarget::TEXTURE_2D, Texture::eTextureParameterType::TEXTURE_BASE_LEVEL, 0);
	TexParameteri(Texture::eBindTarget::TEXTURE_2D, Texture::eTextureParameterType::TEXTURE_MAX_LEVEL, static_cast<int>(mipmapDatas.size() - 1));


	/*
	for (unsigned int i = 0; i < mipmapDatas.size(); i++)
	{
		TexImage2D(i, mipmapDatas[i]);
	}
	*/
}

void SingleTexture::TexImage2D(int level, const void* data) const noexcept
{
	BindTexture();
	
	if (mInternalFormat != eTextureInternalFormat::NONE)
	{
		glTexImage2D(GL_TEXTURE_2D, level, static_cast<unsigned int>(mInternalFormat), mWidth, mHeight, 0, static_cast<unsigned int>(mDataFormat), static_cast<unsigned int>(mDataType), data);
	}
	else if (mCompressedInternalFormat != eTextureCompressedInternalFormat::NONE)
	{
		NEVER_HAPPEN;
	}
	else
	{
		NEVER_HAPPEN;
	}
}

void SingleTexture::TexImage1D(int level, const void* data) const noexcept
{
	BindTexture();
	if (mInternalFormat != eTextureInternalFormat::NONE)
	{
		glTexImage1D(GL_TEXTURE_1D, level, static_cast<unsigned int>(mInternalFormat), mWidth, 0, static_cast<unsigned int>(mDataFormat), static_cast<unsigned int>(mDataType), data);
	}
	else if (mCompressedInternalFormat != eTextureCompressedInternalFormat::NONE)
	{
		NEVER_HAPPEN;
	}
	else
	{
		NEVER_HAPPEN;
	}
}

void SingleTexture::TexImage1D(int level, const DirectX::Image* directXImage) const noexcept
{
	if (mInternalFormat != eTextureInternalFormat::NONE)
	{
		glTexImage1D(GL_TEXTURE_1D, level, static_cast<unsigned int>(mInternalFormat), static_cast<int>(directXImage->width),  0, static_cast<unsigned int>(mDataFormat), static_cast<unsigned int>(mDataType), directXImage->pixels);
	}
	else if (mCompressedInternalFormat != eTextureCompressedInternalFormat::NONE)
	{
		glCompressedTexImage1D(GL_TEXTURE_1D, level, static_cast<unsigned int>(mCompressedInternalFormat), static_cast<int>(directXImage->width), 0, static_cast<int>(directXImage->slicePitch), directXImage->pixels);
	}
	else
	{
		NEVER_HAPPEN;
	}
}

void SingleTexture::TexImage2D(int level, const DirectX::Image* directXImage) const noexcept
{
	if (mInternalFormat != eTextureInternalFormat::NONE)
	{
		glTexImage2D(GL_TEXTURE_2D, level, static_cast<unsigned int>(mInternalFormat), static_cast<int>(directXImage->width), static_cast<int>(directXImage->height), 0, static_cast<unsigned int>(mDataFormat), static_cast<unsigned int>(mDataType), directXImage->pixels);
	}
	else if (mCompressedInternalFormat != eTextureCompressedInternalFormat::NONE)
	{
// 		img.rowPitch = /*<number of bytes in a scanline of the source data>*/;
// 		img.slicePitch = /*<number of bytes in the entire 2D image>*/;
		glCompressedTexImage2D(GL_TEXTURE_2D, level, static_cast<unsigned int>(mCompressedInternalFormat), static_cast<int>(directXImage->width), static_cast<int>(directXImage->height), 0, static_cast<int>(directXImage->slicePitch), directXImage->pixels);
	}
	else
	{
		NEVER_HAPPEN;
	}
}

SingleTexture::SingleTexture(eTextureType textureType, eTargetTexture target, eTextureInternalFormat internalFormat, unsigned int width, eTextureComponentFormat format, eDataType type, std::vector<const DirectX::Image*> mipmapDatas)
	: Texture{ textureType, eBindTarget::TEXTURE_2D, target, internalFormat,  eTextureCompressedInternalFormat::NONE, width, format, type }
{
	Tex2DMipMapImages(mipmapDatas);

	OnEndContructor();
}

SingleTexture::SingleTexture(eTextureType textureType, eTargetTexture target, eTextureInternalFormat internalFormat, unsigned int width, unsigned int height, eTextureComponentFormat format, eDataType type, std::vector<const DirectX::Image*> mipmapDatas)
	: Texture{ textureType, eBindTarget::TEXTURE_2D, target, internalFormat, eTextureCompressedInternalFormat::NONE, width, height, format, type }
{
	Tex2DMipMapImages(mipmapDatas);

	OnEndContructor();
}

SingleTexture::SingleTexture(eTextureType textureType, eTargetTexture target, eTextureCompressedInternalFormat compressedInternalFormat, unsigned int width, eTextureComponentFormat format, eDataType type, std::vector<const DirectX::Image*> mipmapDatas)
	: Texture{ textureType, eBindTarget::TEXTURE_2D, target, eTextureInternalFormat::NONE, compressedInternalFormat, width, format, type }
{
	Tex2DMipMapImages(mipmapDatas);

	OnEndContructor();
}

SingleTexture::SingleTexture(eTextureType textureType, eTargetTexture target, eTextureCompressedInternalFormat compressedInternalFormat, unsigned int width, unsigned int height, eTextureComponentFormat format, eDataType type, std::vector<const DirectX::Image*> mipmapDatas)
	: Texture{ textureType, eBindTarget::TEXTURE_2D, target, eTextureInternalFormat::NONE, compressedInternalFormat, width, height, format, type }
{
	Tex2DMipMapImages(mipmapDatas);

	OnEndContructor();
}
