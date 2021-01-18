#include "Texture.h"

#include "../API/OpenglAPI.h"

static unsigned int BoundId = 0;

Doom::Texture::Texture(unsigned int width, unsigned int height, Texture::TargetTexture targetTexture)
	: Width{ width }, Height{ height }, _TargetTexture{ targetTexture }
{
	glGenTextures(1, &(this->id));
}

Doom::Texture::~Texture()
{
	glDeleteTextures(1, &(this->id));

	
}

std::unordered_map<Doom::Texture::BindTarget, unsigned int> Doom::Texture::BoundId{};

void Doom::Texture::BindTexture()
{
	if (BoundId[this->_BindTarget] == this->id)
	{
		Debug::Log("Texture")
		return;
	}

	glBindTexture(static_cast<unsigned int>(this->_BindTarget), this->id);
	BoundId[this->_BindTarget] = this->id;
}

void Doom::Texture::UnBindTexture()
{
	glBindTexture(static_cast<unsigned int>(this->_BindTarget), 0);
	BoundId[this->_BindTarget] = 0;
}

void Doom::Texture::ActiveTexture(unsigned int index)
{
	glActiveTexture(GL_TEXTURE0 + index);
}

void Doom::Texture::TexImage2D(TargetTexture target, int level, int internalformat, int width, int height, int border, PixelData_DataFormat format, PixelData_DataType type, const void* data)
{
	if (Texture::BoundId != this->id)
	{
		this->BindTexture();
	}

	glTexImage2D(target, level, internalformat, width, height, border, format, type, data);
}
