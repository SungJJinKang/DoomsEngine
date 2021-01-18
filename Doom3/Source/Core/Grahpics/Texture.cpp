#include "Texture.h"

#include "../API/OpenglAPI.h"

static unsigned int BoundId = 0;



Doom::Texture::Texture(TextureType textureType, BindTarget bindTarget, 
	TargetTexture targetTexture, InternalFormat internalFormat, unsigned int width, unsigned int height, DataFormat format, DataType type, const void* data = nullptr)
	: _TextureType{ textureType }, _BindTarget{ bindTarget }, 
	_Target{ targetTexture }, _InternalFormat{ internalFormat }, Width{ width }, Height{ height }, _DataFormat{ format }, _DataType{ type }
{
	//TODO : use glGenTexture(texturecount ~ , ) for multiple textures at once
	glGenTextures(1, &(this->ID));
	this->BindTexture();
	this->TexImage2D(0, _InternalFormat, Width, Height, _DataFormat, _DataType, data);
}

Doom::Texture::~Texture()
{
	glDeleteTextures(1, &(this->ID));

	
}

std::unordered_map<Doom::Texture::BindTarget, unsigned int> Doom::Texture::CurrentBoundId{};

void Doom::Texture::BindTexture()
{
	if (CurrentBoundId[this->_BindTarget] == this->ID)
	{
		DEBUG_LOG("Texture is already bound");
		return;
	}

	glBindTexture(static_cast<unsigned int>(this->_BindTarget), this->ID);
	CurrentBoundId[this->_BindTarget] = this->ID;
}

void Doom::Texture::UnBindTexture()
{
	glBindTexture(static_cast<unsigned int>(this->_BindTarget), 0);
	CurrentBoundId[this->_BindTarget] = 0;
}

void Doom::Texture::ActiveTexture(unsigned int index)
{
	glActiveTexture(GL_TEXTURE0 + index);
}

void Doom::Texture::TexParameterf(BindTarget target, TextureParameterType pname, TextureParameterValue param)
{
	glTexParameterf(static_cast<unsigned int>(target), static_cast<unsigned int>(pname), static_cast<unsigned int>(param));
}

void Doom::Texture::TexParameteri(BindTarget target, TextureParameterType pname, TextureParameterValue param)
{
	glTexParameteri(static_cast<unsigned int>(target), static_cast<unsigned int>(pname), static_cast<unsigned int>(param));
}

