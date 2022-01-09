#include "SingleTexture.h"

#include <DirectXTex.h>

using namespace dooms::graphics;


SingleTexture::SingleTexture()
{
}

SingleTexture::SingleTexture(dooms::graphics::GraphicsAPI::eTextureType textureType, dooms::graphics::GraphicsAPI::eTargetTexture target, dooms::graphics::GraphicsAPI::eTextureInternalFormat internalFormat, UINT32 width, dooms::graphics::GraphicsAPI::eTextureComponentFormat format, dooms::graphics::GraphicsAPI::eDataType type, const void* data)
{
	InitializeSingleTexture(textureType, target, internalFormat, width, format, type, data);
}

SingleTexture::SingleTexture(dooms::graphics::GraphicsAPI::eTextureType textureType, dooms::graphics::GraphicsAPI::eTargetTexture target, dooms::graphics::GraphicsAPI::eTextureInternalFormat internalFormat, UINT32 width, UINT32 height, dooms::graphics::GraphicsAPI::eTextureComponentFormat format, dooms::graphics::GraphicsAPI::eDataType type, const void* data)
{
	InitializeSingleTexture(textureType, target, internalFormat, width, height, format, type, data);
}

SingleTexture::SingleTexture(dooms::graphics::GraphicsAPI::eTextureType textureType, dooms::graphics::GraphicsAPI::eTargetTexture target, dooms::graphics::GraphicsAPI::eTextureCompressedInternalFormat compressedInternalFormat, UINT32 width, dooms::graphics::GraphicsAPI::eTextureComponentFormat format, dooms::graphics::GraphicsAPI::eDataType type, const void* data)
{
	InitializeSingleTexture(textureType, target, compressedInternalFormat, width, format, type, data);
}

SingleTexture::SingleTexture(dooms::graphics::GraphicsAPI::eTextureType textureType, dooms::graphics::GraphicsAPI::eTargetTexture target, dooms::graphics::GraphicsAPI::eTextureCompressedInternalFormat compressedInternalFormat, UINT32 width, UINT32 height, dooms::graphics::GraphicsAPI::eTextureComponentFormat format, dooms::graphics::GraphicsAPI::eDataType type, const void* data)
{
	InitializeSingleTexture(textureType, target, compressedInternalFormat, width, height, format, type, data);
}

SingleTexture::SingleTexture(dooms::graphics::GraphicsAPI::eTextureType textureType, dooms::graphics::GraphicsAPI::eTargetTexture target, dooms::graphics::GraphicsAPI::eTextureInternalFormat internalFormat, UINT32 width, dooms::graphics::GraphicsAPI::eTextureComponentFormat format, dooms::graphics::GraphicsAPI::eDataType type, std::vector<const DirectX::Image*> mipmapDatas)
{
	InitializeSingleTexture(textureType, target, internalFormat, width, format, type, mipmapDatas);
}

SingleTexture::SingleTexture(dooms::graphics::GraphicsAPI::eTextureType textureType, dooms::graphics::GraphicsAPI::eTargetTexture target, dooms::graphics::GraphicsAPI::eTextureInternalFormat internalFormat, UINT32 width, UINT32 height, dooms::graphics::GraphicsAPI::eTextureComponentFormat format, dooms::graphics::GraphicsAPI::eDataType type, std::vector<const DirectX::Image*> mipmapDatas)
{
	InitializeSingleTexture(textureType, target, internalFormat, width, height, format, type, mipmapDatas);
}

SingleTexture::SingleTexture(dooms::graphics::GraphicsAPI::eTextureType textureType, dooms::graphics::GraphicsAPI::eTargetTexture target, dooms::graphics::GraphicsAPI::eTextureCompressedInternalFormat compressedInternalFormat, UINT32 width, dooms::graphics::GraphicsAPI::eTextureComponentFormat format, dooms::graphics::GraphicsAPI::eDataType type, std::vector<const DirectX::Image*> mipmapDatas)
{
	InitializeSingleTexture(textureType, target, compressedInternalFormat, width, format, type, mipmapDatas);
}

SingleTexture::SingleTexture(dooms::graphics::GraphicsAPI::eTextureType textureType, dooms::graphics::GraphicsAPI::eTargetTexture target, dooms::graphics::GraphicsAPI::eTextureCompressedInternalFormat compressedInternalFormat, UINT32 width, UINT32 height, dooms::graphics::GraphicsAPI::eTextureComponentFormat format, dooms::graphics::GraphicsAPI::eDataType type, std::vector<const DirectX::Image*> mipmapDatas)
{
	InitializeSingleTexture(textureType, target, compressedInternalFormat, width, height, format, type, mipmapDatas);
}

void SingleTexture::InitializeSingleTexture(dooms::graphics::GraphicsAPI::eTextureType textureType, dooms::graphics::GraphicsAPI::eTargetTexture target,
	dooms::graphics::GraphicsAPI::eTextureInternalFormat internalFormat, UINT32 width, dooms::graphics::GraphicsAPI::eTextureComponentFormat format, dooms::graphics::GraphicsAPI::eDataType type,
	const void* data)
{
	InitializeTexture(textureType, dooms::graphics::GraphicsAPI::eTextureBindTarget::TEXTURE_2D, target, internalFormat, dooms::graphics::GraphicsAPI::eTextureCompressedInternalFormat::TEXTURE_COMPRESSED_INTERNAL_FORMAT_NONE, width, format, type);

	TexImage1D(0, data);

	OnEndContructor();
}

void SingleTexture::InitializeSingleTexture(dooms::graphics::GraphicsAPI::eTextureType textureType, dooms::graphics::GraphicsAPI::eTargetTexture target,
	dooms::graphics::GraphicsAPI::eTextureInternalFormat internalFormat, UINT32 width, UINT32 height, dooms::graphics::GraphicsAPI::eTextureComponentFormat format, dooms::graphics::GraphicsAPI::eDataType type,
	const void* data)
{
	InitializeTexture(textureType, dooms::graphics::GraphicsAPI::eTextureBindTarget::TEXTURE_2D, target, internalFormat, dooms::graphics::GraphicsAPI::eTextureCompressedInternalFormat::TEXTURE_COMPRESSED_INTERNAL_FORMAT_NONE, width, height, format, type);

	TexImage2D(0, data);

	OnEndContructor();
}

void SingleTexture::InitializeSingleTexture(dooms::graphics::GraphicsAPI::eTextureType textureType, dooms::graphics::GraphicsAPI::eTargetTexture target,
	dooms::graphics::GraphicsAPI::eTextureCompressedInternalFormat compressedInternalFormat, UINT32 width, dooms::graphics::GraphicsAPI::eTextureComponentFormat format,
	dooms::graphics::GraphicsAPI::eDataType type, const void* data)
{
	InitializeTexture(textureType, dooms::graphics::GraphicsAPI::eTextureBindTarget::TEXTURE_2D, target, dooms::graphics::GraphicsAPI::eTextureInternalFormat::TEXTURE_INTERNAL_FORMAT_NONE, compressedInternalFormat, width, format, type);

	TexImage1D(0, data);

	OnEndContructor();
}

void SingleTexture::InitializeSingleTexture(dooms::graphics::GraphicsAPI::eTextureType textureType, dooms::graphics::GraphicsAPI::eTargetTexture target,
	dooms::graphics::GraphicsAPI::eTextureCompressedInternalFormat compressedInternalFormat, UINT32 width, UINT32 height,
	dooms::graphics::GraphicsAPI::eTextureComponentFormat format, dooms::graphics::GraphicsAPI::eDataType type, const void* data)
{
	InitializeTexture(textureType, dooms::graphics::GraphicsAPI::eTextureBindTarget::TEXTURE_2D, target, dooms::graphics::GraphicsAPI::eTextureInternalFormat::TEXTURE_INTERNAL_FORMAT_NONE, compressedInternalFormat, width, height, format, type);

	TexImage2D(0, data);

	OnEndContructor();
}

void SingleTexture::InitializeSingleTexture(dooms::graphics::GraphicsAPI::eTextureType textureType, dooms::graphics::GraphicsAPI::eTargetTexture target,
	dooms::graphics::GraphicsAPI::eTextureInternalFormat internalFormat, UINT32 width, dooms::graphics::GraphicsAPI::eTextureComponentFormat format, dooms::graphics::GraphicsAPI::eDataType type,
	std::vector<const DirectX::Image*> mipmapDatas)
{
	InitializeTexture(textureType, dooms::graphics::GraphicsAPI::eTextureBindTarget::TEXTURE_2D, target, internalFormat, dooms::graphics::GraphicsAPI::eTextureCompressedInternalFormat::TEXTURE_COMPRESSED_INTERNAL_FORMAT_NONE, width, format, type);
	
	Tex2DMipMapImages(mipmapDatas);
	OnEndContructor();
}

void SingleTexture::InitializeSingleTexture(dooms::graphics::GraphicsAPI::eTextureType textureType, dooms::graphics::GraphicsAPI::eTargetTexture target,
	dooms::graphics::GraphicsAPI::eTextureInternalFormat internalFormat, UINT32 width, UINT32 height, dooms::graphics::GraphicsAPI::eTextureComponentFormat format, dooms::graphics::GraphicsAPI::eDataType type,
	std::vector<const DirectX::Image*> mipmapDatas)
{
	InitializeTexture(textureType, dooms::graphics::GraphicsAPI::eTextureBindTarget::TEXTURE_2D, target, internalFormat, dooms::graphics::GraphicsAPI::eTextureCompressedInternalFormat::TEXTURE_COMPRESSED_INTERNAL_FORMAT_NONE, width, height, format, type);

	Tex2DMipMapImages(mipmapDatas);

	OnEndContructor();
}

void SingleTexture::InitializeSingleTexture(dooms::graphics::GraphicsAPI::eTextureType textureType, dooms::graphics::GraphicsAPI::eTargetTexture target,
	dooms::graphics::GraphicsAPI::eTextureCompressedInternalFormat compressedInternalFormat, UINT32 width, dooms::graphics::GraphicsAPI::eTextureComponentFormat format,
	dooms::graphics::GraphicsAPI::eDataType type, std::vector<const DirectX::Image*> mipmapDatas)
{
	InitializeTexture(textureType, dooms::graphics::GraphicsAPI::eTextureBindTarget::TEXTURE_2D, target, dooms::graphics::GraphicsAPI::eTextureInternalFormat::TEXTURE_INTERNAL_FORMAT_NONE, compressedInternalFormat, width, format, type);

	Tex2DMipMapImages(mipmapDatas);

	OnEndContructor();
}

void SingleTexture::InitializeSingleTexture(dooms::graphics::GraphicsAPI::eTextureType textureType, dooms::graphics::GraphicsAPI::eTargetTexture target,
	dooms::graphics::GraphicsAPI::eTextureCompressedInternalFormat compressedInternalFormat, UINT32 width, UINT32 height,
	dooms::graphics::GraphicsAPI::eTextureComponentFormat format, dooms::graphics::GraphicsAPI::eDataType type, std::vector<const DirectX::Image*> mipmapDatas)
{
	InitializeTexture(textureType, dooms::graphics::GraphicsAPI::eTextureBindTarget::TEXTURE_2D, target, dooms::graphics::GraphicsAPI::eTextureInternalFormat::TEXTURE_INTERNAL_FORMAT_NONE, compressedInternalFormat, width, height, format, type);

	Tex2DMipMapImages(mipmapDatas);

	OnEndContructor();
}



void dooms::graphics::SingleTexture::Tex2DMipMapImages(std::vector<const DirectX::Image*> mipmapDatas)
{
	BindTexture();

	if (mInternalFormat != dooms::graphics::GraphicsAPI::eTextureInternalFormat::TEXTURE_INTERNAL_FORMAT_NONE)
	{
		for (UINT32 i = 0; i < mipmapDatas.size(); i++)
		{
			GraphicsAPI::Define2DTextureStorageRequirement(mBindTarget, i, mInternalFormat, mipmapDatas[i]->width, mipmapDatas[i]->height);
			GraphicsAPI::UploadPixelsTo2DTexture(mTarget, i, 0, 0, mipmapDatas[i]->width, mipmapDatas[i]->height, mDataFormat, mDataType, mipmapDatas[i]->pixels);
		}

	}
	else if (mCompressedInternalFormat != dooms::graphics::GraphicsAPI::eTextureCompressedInternalFormat::TEXTURE_COMPRESSED_INTERNAL_FORMAT_NONE)
	{
		for (UINT32 i = 0; i < mipmapDatas.size(); i++)
		{
			GraphicsAPI::Define2DCompressedTextureStorageRequirement(mBindTarget, i, mCompressedInternalFormat, mipmapDatas[i]->width, mipmapDatas[i]->height);
			GraphicsAPI::UploadPixelsTo2DCompressedTexture(mTarget, i, 0, 0, mipmapDatas[i]->width, mipmapDatas[i]->height, mDataFormat, mDataType, mipmapDatas[i]->pixels);
		}

	}
	else
	{
		NEVER_HAPPEN;
	}

	
	TexParameteri(dooms::graphics::GraphicsAPI::eTextureBindTarget::TEXTURE_2D, GraphicsAPI::eTextureParameterType::TEXTURE_BASE_LEVEL, 0);
	TexParameteri(dooms::graphics::GraphicsAPI::eTextureBindTarget::TEXTURE_2D, GraphicsAPI::eTextureParameterType::TEXTURE_MAX_LEVEL, static_cast<INT32>(mipmapDatas.size() - 1));


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
	
	if (mInternalFormat != dooms::graphics::GraphicsAPI::eTextureInternalFormat::TEXTURE_INTERNAL_FORMAT_NONE)
	{
		GraphicsAPI::Define2DTextureStorageRequirement(mBindTarget, 0, mInternalFormat, mWidth, mHeight);
		GraphicsAPI::UploadPixelsTo2DTexture(mTarget, 0, 0, 0, mWidth, mHeight, mDataFormat, mDataType, data);
	}
	else if (mCompressedInternalFormat != dooms::graphics::GraphicsAPI::eTextureCompressedInternalFormat::TEXTURE_COMPRESSED_INTERNAL_FORMAT_NONE)
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
	if (mInternalFormat != dooms::graphics::GraphicsAPI::eTextureInternalFormat::TEXTURE_INTERNAL_FORMAT_NONE)
	{
		GraphicsAPI::Define1DTextureStorageRequirement(mBindTarget, 0, mInternalFormat, mWidth);
		GraphicsAPI::UploadPixelsTo1DTexture(mTarget, 0, 0, mWidth, mDataFormat, mDataType, data);
	}
	else if (mCompressedInternalFormat != dooms::graphics::GraphicsAPI::eTextureCompressedInternalFormat::TEXTURE_COMPRESSED_INTERNAL_FORMAT_NONE)
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
	if (mInternalFormat != dooms::graphics::GraphicsAPI::eTextureInternalFormat::TEXTURE_INTERNAL_FORMAT_NONE)
	{
		GraphicsAPI::Define1DTextureStorageRequirement(mBindTarget, 0, mInternalFormat, directXImage->width);
		GraphicsAPI::UploadPixelsTo1DTexture(mTarget, 0, 0, directXImage->width, mDataFormat, mDataType, directXImage->pixels);
	}
	else if (mCompressedInternalFormat != dooms::graphics::GraphicsAPI::eTextureCompressedInternalFormat::TEXTURE_COMPRESSED_INTERNAL_FORMAT_NONE)
	{
		GraphicsAPI::Define1DCompressedTextureStorageRequirement(mBindTarget, 0, mCompressedInternalFormat, directXImage->width);
		GraphicsAPI::UploadPixelsTo1DCompressedTexture(mTarget, 0, 0, directXImage->width, mDataFormat, mDataType, directXImage->pixels);
	}
	else
	{
		NEVER_HAPPEN;
	}
}

void SingleTexture::TexImage2D(INT32 level, const DirectX::Image* directXImage) const noexcept
{
	if (mInternalFormat != dooms::graphics::GraphicsAPI::eTextureInternalFormat::TEXTURE_INTERNAL_FORMAT_NONE)
	{
		GraphicsAPI::Define2DTextureStorageRequirement(mBindTarget, 0, mInternalFormat, directXImage->width, directXImage->height);
		GraphicsAPI::UploadPixelsTo2DTexture(mTarget, 0, 0, 0, directXImage->width, directXImage->height, mDataFormat, mDataType, directXImage->pixels);
	}
	else if (mCompressedInternalFormat != dooms::graphics::GraphicsAPI::eTextureCompressedInternalFormat::TEXTURE_COMPRESSED_INTERNAL_FORMAT_NONE)
	{
		GraphicsAPI::Define2DCompressedTextureStorageRequirement(mBindTarget, 0, mCompressedInternalFormat, directXImage->width, directXImage->height);
		GraphicsAPI::UploadPixelsTo2DCompressedTexture(mTarget, 0, 0, 0, directXImage->width, directXImage->height, mDataFormat, mDataType, directXImage->pixels);
	}
	else
	{
		NEVER_HAPPEN;
	}
}




