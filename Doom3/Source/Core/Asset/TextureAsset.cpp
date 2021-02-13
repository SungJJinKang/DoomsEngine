#include "TextureAsset.h"

#include "../Graphics/Texture.h"
#include "../Graphics/SingleTexture.h"

using namespace doom::graphics;


doom::TextureAsset::TextureAsset(int width, int height, int componentCount, unsigned char* data)
	: mWidth{ width }, mHeight{ height }, mComponentType{ static_cast<eTextureComponent>(componentCount) }, mData{ data }
{

}

void doom::TextureAsset::OnEndImportInMainThread()
{
	this->CreateTexture();
}

void doom::TextureAsset::CreateTexture()
{
	Texture::eInternalFormat internalFormat;
	switch (this->mComponentType)
	{
	case eTextureComponent::Grey:
		internalFormat = Texture::eInternalFormat::DEPTH_COMPONENT;
		break;

	case eTextureComponent::GreyAlpha:
		internalFormat = Texture::eInternalFormat::DEPTH_STENCIL;
		break;

	case eTextureComponent::RGB:
		internalFormat = Texture::eInternalFormat::RGB;
		break;

	case eTextureComponent::RGBA:
		internalFormat = Texture::eInternalFormat::RGBA;
		break;

	default:
		NODEFAULT;
	}

	Texture::eDataFormat dataFormat;
	switch (this->mComponentType)
	{
	case eTextureComponent::Grey:
		dataFormat = Texture::eDataFormat::DEPTH_COMPONENT;
		break;

	case eTextureComponent::GreyAlpha:
		dataFormat = Texture::eDataFormat::DEPTH_STENCIL;
		break;

	case eTextureComponent::RGB:
		dataFormat = Texture::eDataFormat::RGB;
		break;

	case eTextureComponent::RGBA:
		dataFormat = Texture::eDataFormat::RGBA;
		break;

	default:
		NODEFAULT;
	}

	Texture::eDataType dataType;
	switch (this->mComponentType)
	{
	case eTextureComponent::Grey:
		dataType = Texture::eDataType::UNSIGNED_BYTE;
		break;

	case eTextureComponent::GreyAlpha:
		dataType = Texture::eDataType::UNSIGNED_BYTE;
		break;

	case eTextureComponent::RGB:
		dataType = Texture::eDataType::UNSIGNED_BYTE;
		break;

	case eTextureComponent::RGBA:
		dataType = Texture::eDataType::UNSIGNED_BYTE;
		break;

	default:
		NODEFAULT;
	}


	this->mTexture =
		new graphics::SingleTexture(Texture::eTextureType::DIFFUSE, Texture::eTargetTexture::TEXTURE_2D, internalFormat, mWidth, mHeight, dataFormat, dataType, mData);
}