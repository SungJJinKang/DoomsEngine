#include "SingleTexture.h"

#include <DirectXTex.h>

using namespace doom::graphics;


SingleTexture::SingleTexture(eTextureType textureType, eTargetTexture target, eTextureInternalFormat internalFormat, UINT32 width, eTextureComponentFormat format, eDataType type, const void* data)
	: Texture{ textureType, eBindTarget::TEXTURE_2D, target, internalFormat, eTextureCompressedInternalFormat::NONE, width, format, type }
{
	TexImage1D(0, data);

	OnEndContructor();
}

SingleTexture::SingleTexture(eTextureType textureType, eTargetTexture target, eTextureInternalFormat internalFormat, UINT32 width, UINT32 height, eTextureComponentFormat format, eDataType type, const void* data)
	: Texture{textureType, eBindTarget::TEXTURE_2D, target, internalFormat, eTextureCompressedInternalFormat::NONE, width, height, format, type }
{
	TexImage2D(0, data);

	OnEndContructor();
}

SingleTexture::SingleTexture(eTextureType textureType, eTargetTexture target, eTextureCompressedInternalFormat compressedInternalFormat, UINT32 width, eTextureComponentFormat format, eDataType type, const void* data)
	: Texture{ textureType, eBindTarget::TEXTURE_2D, target, eTextureInternalFormat::NONE, compressedInternalFormat, width, format, type }
{
	TexImage2D(0, data);

	OnEndContructor();
}

SingleTexture::SingleTexture(eTextureType textureType, eTargetTexture target, eTextureCompressedInternalFormat compressedInternalFormat, UINT32 width, UINT32 height, eTextureComponentFormat format, eDataType type, const void* data)
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
		for (UINT32 i = 0; i < mipmapDatas.size(); i++)
		{
			glTexImage2D(GL_TEXTURE_2D, i, static_cast<UINT32>(mInternalFormat), static_cast<INT32>(mipmapDatas[i]->width), static_cast<INT32>(mipmapDatas[i]->height), 0, static_cast<UINT32>(mDataFormat), static_cast<UINT32>(mDataType), mipmapDatas[i]->pixels);
		}

	}
	else if (mCompressedInternalFormat != eTextureCompressedInternalFormat::NONE)
	{
		for (UINT32 i = 0; i < mipmapDatas.size(); i++)
		{
			glCompressedTexImage2D(GL_TEXTURE_2D, i, static_cast<UINT32>(mCompressedInternalFormat), static_cast<INT32>(mipmapDatas[i]->width), static_cast<INT32>(mipmapDatas[i]->height), 0, static_cast<INT32>(mipmapDatas[i]->slicePitch), mipmapDatas[i]->pixels);
		}

	}
	else
	{
		NEVER_HAPPEN;
	}

	
	TexParameteri(Texture::eBindTarget::TEXTURE_2D, Texture::eTextureParameterType::TEXTURE_BASE_LEVEL, 0);
	TexParameteri(Texture::eBindTarget::TEXTURE_2D, Texture::eTextureParameterType::TEXTURE_MAX_LEVEL, static_cast<INT32>(mipmapDatas.size() - 1));


	/*
	for (UINT32 i = 0; i < mipmapDatas.size(); i++)
	{
		TexImage2D(i, mipmapDatas[i]);
	}
	*/
}

void SingleTexture::TexImage2D(INT32 level, const void* data) const noexcept
{
	BindTexture();
	
	if (mInternalFormat != eTextureInternalFormat::NONE)
	{
		glTexImage2D(GL_TEXTURE_2D, level, static_cast<UINT32>(mInternalFormat), mWidth, mHeight, 0, static_cast<UINT32>(mDataFormat), static_cast<UINT32>(mDataType), data);
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

void SingleTexture::TexImage1D(INT32 level, const void* data) const noexcept
{
	BindTexture();
	if (mInternalFormat != eTextureInternalFormat::NONE)
	{
		glTexImage1D(GL_TEXTURE_1D, level, static_cast<UINT32>(mInternalFormat), mWidth, 0, static_cast<UINT32>(mDataFormat), static_cast<UINT32>(mDataType), data);
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

void SingleTexture::TexImage1D(INT32 level, const DirectX::Image* directXImage) const noexcept
{
	if (mInternalFormat != eTextureInternalFormat::NONE)
	{
		glTexImage1D(GL_TEXTURE_1D, level, static_cast<UINT32>(mInternalFormat), static_cast<INT32>(directXImage->width),  0, static_cast<UINT32>(mDataFormat), static_cast<UINT32>(mDataType), directXImage->pixels);
	}
	else if (mCompressedInternalFormat != eTextureCompressedInternalFormat::NONE)
	{
		glCompressedTexImage1D(GL_TEXTURE_1D, level, static_cast<UINT32>(mCompressedInternalFormat), static_cast<INT32>(directXImage->width), 0, static_cast<INT32>(directXImage->slicePitch), directXImage->pixels);
	}
	else
	{
		NEVER_HAPPEN;
	}
}

void SingleTexture::TexImage2D(INT32 level, const DirectX::Image* directXImage) const noexcept
{
	if (mInternalFormat != eTextureInternalFormat::NONE)
	{
		glTexImage2D(GL_TEXTURE_2D, level, static_cast<UINT32>(mInternalFormat), static_cast<INT32>(directXImage->width), static_cast<INT32>(directXImage->height), 0, static_cast<UINT32>(mDataFormat), static_cast<UINT32>(mDataType), directXImage->pixels);
	}
	else if (mCompressedInternalFormat != eTextureCompressedInternalFormat::NONE)
	{
// 		img.rowPitch = /*<number of bytes in a scanline of the source data>*/;
// 		img.slicePitch = /*<number of bytes in the entire 2D image>*/;
		glCompressedTexImage2D(GL_TEXTURE_2D, level, static_cast<UINT32>(mCompressedInternalFormat), static_cast<INT32>(directXImage->width), static_cast<INT32>(directXImage->height), 0, static_cast<INT32>(directXImage->slicePitch), directXImage->pixels);
	}
	else
	{
		NEVER_HAPPEN;
	}
}

SingleTexture::SingleTexture(eTextureType textureType, eTargetTexture target, eTextureInternalFormat internalFormat, UINT32 width, eTextureComponentFormat format, eDataType type, std::vector<const DirectX::Image*> mipmapDatas)
	: Texture{ textureType, eBindTarget::TEXTURE_2D, target, internalFormat,  eTextureCompressedInternalFormat::NONE, width, format, type }
{
	Tex2DMipMapImages(mipmapDatas);

	OnEndContructor();
}

SingleTexture::SingleTexture(eTextureType textureType, eTargetTexture target, eTextureInternalFormat internalFormat, UINT32 width, UINT32 height, eTextureComponentFormat format, eDataType type, std::vector<const DirectX::Image*> mipmapDatas)
	: Texture{ textureType, eBindTarget::TEXTURE_2D, target, internalFormat, eTextureCompressedInternalFormat::NONE, width, height, format, type }
{
	Tex2DMipMapImages(mipmapDatas);

	OnEndContructor();
}

SingleTexture::SingleTexture(eTextureType textureType, eTargetTexture target, eTextureCompressedInternalFormat compressedInternalFormat, UINT32 width, eTextureComponentFormat format, eDataType type, std::vector<const DirectX::Image*> mipmapDatas)
	: Texture{ textureType, eBindTarget::TEXTURE_2D, target, eTextureInternalFormat::NONE, compressedInternalFormat, width, format, type }
{
	Tex2DMipMapImages(mipmapDatas);

	OnEndContructor();
}

SingleTexture::SingleTexture(eTextureType textureType, eTargetTexture target, eTextureCompressedInternalFormat compressedInternalFormat, UINT32 width, UINT32 height, eTextureComponentFormat format, eDataType type, std::vector<const DirectX::Image*> mipmapDatas)
	: Texture{ textureType, eBindTarget::TEXTURE_2D, target, eTextureInternalFormat::NONE, compressedInternalFormat, width, height, format, type }
{
	Tex2DMipMapImages(mipmapDatas);

	OnEndContructor();
}
