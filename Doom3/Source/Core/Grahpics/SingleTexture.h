#pragma once

#include "Texture.h"

namespace Doom
{
	class SingleTexture : public Texture
	{
	private:

	public:
		//SingleTexture
		SingleTexture(TextureType textureType, 
			TargetTexture target, InternalFormat internalFormat, unsigned int width, unsigned int height, DataFormat format, DataType type, const void* data);


		void TexImage2D(int level, InternalFormat internalformat, int width, int height, DataFormat format, DataType type, const void* data) final;

	};

}